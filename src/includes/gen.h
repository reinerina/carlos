//
// Created by 陈洋 on 24-11-4.
//

#ifndef GEN_H
#define GEN_H
#include "ast.h"
#include "table.h"
namespace carlos {
class IRGen {
 public:
  explicit IRGen(const std::shared_ptr<ASTNode> &root) : root(root) {}

  void gen() { gen_node(root); }

 private:
  void gen_node(const std::shared_ptr<ASTNode> &node);

  void gen_program(const std::shared_ptr<ProgramNode> &node);

  void gen_entry(const std::shared_ptr<EntryNode> &node);

  void gen_statement(const std::shared_ptr<StatementNode> &node);

  void gen_declaration(const std::shared_ptr<DeclarationStatementNode> &node);

  void gen_if(const std::shared_ptr<IfStatementNode> &node);

  void gen_while(const std::shared_ptr<WhileStatementNode> &node);

  void gen_for(const std::shared_ptr<ForStatementNode> &node);

  void gen_control(const std::shared_ptr<ControlStatementNode> &node) const;

  int gen_expression(const std::shared_ptr<ExpressionNode> &node);

  [[nodiscard]] std::shared_ptr<Symbol> get_symbol(const std::string &name) {
    for (auto &scope : scopes | std::views::reverse) {
      if (scope.contains(name)) {
        return scope[name];
      }
    }
    return nullptr;
  }

  void enter_scope() {
    scopes.emplace_back();
    for (const auto &[name, symbol] : symbols_in_next_scope) {
      add_symbol(symbol);
    }
    symbols_in_next_scope.clear();
  }

  void exit_scope() { scopes.pop_back(); }

  void add_symbol(const std::shared_ptr<Symbol> &symbol) {
    scopes.back()[symbol->name] = symbol;
  }

  void add_symbol(const std::string &name, const std::string &alias,
                  const std::variant<std::nullptr_t, int, bool, char, float,
                                     Range, std::shared_ptr<Array>> &value) {
    add_symbol(std::make_shared<Symbol>(name, alias, value));
  }

  void add_symbol_to_next_scope(const std::shared_ptr<Symbol> &symbol) {
    symbols_in_next_scope[symbol->name] = symbol;
  }

  void add_symbol_to_next_scope(
      const std::string &name, const std::string &alias,
      const std::variant<std::nullptr_t, int, bool, char, float, Range,
                         std::shared_ptr<Array>> &value) {
    add_symbol_to_next_scope(std::make_shared<Symbol>(name, alias, value));
  }

  int get_label(const std::string &name) {
    if (labels.contains(name)) {
      labels[name]++;
      return labels[name];
    }
    labels[name] = 0;
    return 0;
  }

  [[nodiscard]] int current_label() const { return temp_label; }
  [[nodiscard]] int current_while_label() const { return while_label; }
  [[nodiscard]] int current_if_label() const { return if_label; }
  [[nodiscard]] int current_for_label() const { return for_label; }
  int next_label() { return ++temp_label; }
  int next_while_label() { return ++while_label; }
  int next_if_label() { return ++if_label; }
  int next_for_label() { return ++for_label; }

  std::shared_ptr<ASTNode> root;
  std::vector<std::unordered_map<std::string, std::shared_ptr<Symbol>>>
      scopes{};
  std::unordered_map<std::string, int> labels{};
  std::vector<int> control_stage{};
  int control_stage_index{};
  int temp_label{};
  int while_label{};
  int if_label{};
  int begin_if{};
  int for_label{};
  bool array_pointer{};
  std::tuple<int, int, bool> range_labels{};
  std::unordered_map<std::string, std::shared_ptr<Symbol>>
      symbols_in_next_scope{};
};
}  // namespace carlos
#endif  // GEN_H
