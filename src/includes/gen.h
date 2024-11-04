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

  void gen_call(const std::shared_ptr<CallStatementNode> &node);

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
  int next_label() { return ++temp_label; }

  std::shared_ptr<ASTNode> root;
  std::vector<std::unordered_map<std::string, std::shared_ptr<Symbol>>>
      scopes{};
  std::unordered_map<std::string, int> labels{};
  int temp_label = 0;
  std::unordered_map<std::string, std::shared_ptr<Symbol>>
      symbols_in_next_scope{};
};
}  // namespace carlos
#endif  // GEN_H
