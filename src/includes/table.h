//
// Created by 陈洋 on 24-11-2.
//

#ifndef TABLE_H
#define TABLE_H
#include <ranges>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <glog/logging.h>
#include "carlos.h"
#include "ast.h"

namespace carlos {
class Symbol;
class SymbolTable;
class SymbolScope;

enum class SymbolType { INT, FLOAT, CHAR, BOOL, VOID, UNKNOWN };

enum class SymbolKind { VARIABLE, FUNCTION, PARAMETER };

class Symbol {
 public:
  Symbol(std::string name,
         const std::variant<std::nullptr_t, int, bool, char, float, Range,
                            std::shared_ptr<Array>> &value,
         const SymbolKind kind, const bool mutability)
      : name(std::move(name)),
        kind(kind),
        value(value),
        mutability(mutability) {
    type = get_type(value);
    if (std::holds_alternative<std::shared_ptr<Array>>(value)) {
      cal_dimensions(std::get<std::shared_ptr<Array>>(value));
    }
  }
  Symbol(std::string name, std::string alias,
         const std::variant<std::nullptr_t, int, bool, char, float, Range,
                            std::shared_ptr<Array>> &value)
      : name(std::move(name)), alias(std::move(alias)), value(value) {
    type = get_type(value);
    if (std::holds_alternative<std::shared_ptr<Array>>(value)) {
      cal_dimensions(std::get<std::shared_ptr<Array>>(value));
    }
  }

  static SymbolType get_type(
      const std::variant<std::nullptr_t, int, bool, char, float, Range,
                         std::shared_ptr<Array>> &value) {
    if (std::holds_alternative<int>(value)) {
      return SymbolType::INT;
    }
    if (std::holds_alternative<float>(value)) {
      return SymbolType::FLOAT;
    }
    if (std::holds_alternative<char>(value)) {
      return SymbolType::CHAR;
    }
    if (std::holds_alternative<bool>(value)) {
      return SymbolType::BOOL;
    }
    if (std::holds_alternative<Range>(value)) {
      return SymbolType::INT;
    }
    if (std::holds_alternative<std::shared_ptr<Array>>(value)) {
      return get_type(std::get<std::shared_ptr<Array>>(value)->values[0]);
    }
    return SymbolType::UNKNOWN;
  }

  void cal_dimensions(const std::shared_ptr<Array> &array) {
    dimensions.push_back(static_cast<int>(array->values.size()));
    if (std::holds_alternative<std::shared_ptr<Array>>(array->values[0])) {
      cal_dimensions(std::get<std::shared_ptr<Array>>(array->values[0]));
    }
  }

  std::string name{};
  std::string alias{};
  SymbolKind kind{};
  SymbolType type = SymbolType::UNKNOWN;
  std::vector<int> dimensions{};

  std::variant<std::nullptr_t, int, bool, char, float, Range,
               std::shared_ptr<Array>>
      value{};
  bool mutability{};
};

class SymbolScope {
 public:
  SymbolScope() = default;

  void add_symbol(const std::shared_ptr<Symbol> &symbol) {
    symbols[symbol->name] = symbol;
  }

  std::shared_ptr<Symbol> get_symbol(const std::string &name) {
    if (symbols.contains(name)) {
      return symbols[name];
    }
    return nullptr;
  }

  std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols{};
};

class SymbolTable {
 public:
  explicit SymbolTable(const std::shared_ptr<ASTNode> &root) : root(root) {}
  SymbolTable(const std::shared_ptr<ASTNode> &root, const bool display)
      : root(root), display(display) {}

  void process() { process_node(root); }

 private:
  void enter_scope() {
    scopes.push_back(std::make_shared<SymbolScope>());
    for (const auto &[name, symbol] : symbols_in_next_scope) {
      add_symbol(symbol);
    }
    symbols_in_next_scope.clear();
  }

  void exit_scope() {
    CHECK_NE(scopes.size(), 0) << "No scope to exit";
    if (display) {
      print_title();
      print_scope();
    }
    scopes.pop_back();
  }

  void print_title() const {
    std::cout << "Scope " << scopes.size() << std::endl;
    std::cout << "Symbol Name\t\tSymbol Type\t\tSymbol Kind\t\tMutability"
              << std::endl;
  }

  void print_scope() const {
    CHECK_NE(scopes.size(), 0) << "No scope to print";
    if (scopes.back()->symbols.empty()) {
      std::cout << "No symbols in this scope" << std::endl;
      return;
    }
    for (const auto &scope = scopes.back();
         const auto &[name, symbol] : scope->symbols) {
      std::cout << name << "\t\t\t\t";
      switch (symbol->type) {
        case SymbolType::INT:
          std::cout << "i32";
          break;
        case SymbolType::FLOAT:
          std::cout << "f32";
          break;
        case SymbolType::CHAR:
          std::cout << "char";
          break;
        case SymbolType::BOOL:
          std::cout << "bool";
          break;
        case SymbolType::VOID:
          std::cout << "void";
          break;
        case SymbolType::UNKNOWN:
          std::cout << "unknown";
          break;
        default: {
          LOG(FATAL) << "Unknown type";
        }
      }
      for (const auto &dim : symbol->dimensions) {
        std::cout << "[" << dim << "]";
      }
      std::cout << "\t\t\t\t";
      switch (symbol->kind) {
        case SymbolKind::VARIABLE:
          std::cout << "variable\t\t";
          break;
        case SymbolKind::FUNCTION:
          std::cout << "function\t\t";
          break;
        case SymbolKind::PARAMETER:
          std::cout << "parameter\t\t";
          break;
        default:
          LOG(FATAL) << "Unknown kind";
      }
      std::cout << std::boolalpha << symbol->mutability << std::endl;
    }
  }

  [[nodiscard]] std::shared_ptr<SymbolScope> current_scope() const {
    CHECK_NE(scopes.size(), 0) << "No scope to get";
    return scopes.back();
  }

  void add_symbol(const std::shared_ptr<Symbol> &symbol) const {
    CHECK_NE(scopes.size(), 0) << "No scope to add symbol";
    if (display && current_scope()->symbols.contains(symbol->name)) {
      print_title();
      print_scope();
    }
    scopes.back()->add_symbol(symbol);
  }

  void add_symbol(const std::string &name,
                  const std::variant<std::nullptr_t, int, bool, char, float,
                                     Range, std::shared_ptr<Array>> &value,
                  const SymbolKind kind, const bool mutability) const {
    CHECK_NE(scopes.size(), 0) << "No scope to add symbol";
    add_symbol(std::make_shared<Symbol>(name, value, kind, mutability));
  }

  void add_symbol_to_next_scope(const std::shared_ptr<Symbol> &symbol) {
    symbols_in_next_scope[symbol->name] = symbol;
  }

  void add_symbol_to_next_scope(
      const std::string &name,
      const std::variant<std::nullptr_t, int, bool, char, float, Range,
                         std::shared_ptr<Array>> &value,
      const SymbolKind kind, const bool mutability) {
    add_symbol_to_next_scope(
        std::make_shared<Symbol>(name, value, kind, mutability));
  }

  [[nodiscard]] std::shared_ptr<Symbol> get_symbol(
      const std::string &name) const {
    for (const auto &scope : scopes | std::views::reverse) {
      if (const auto symbol = scope->get_symbol(name)) {
        return symbol;
      }
    }
    return nullptr;
  }

  void process_node(const std::shared_ptr<ASTNode> &node);

  void process_program(const std::shared_ptr<ProgramNode> &program);

  void process_entry(const std::shared_ptr<EntryNode> &entry);

  void process_statement(const std::shared_ptr<StatementNode> &statement);

  void process_declaration(
      const std::shared_ptr<DeclarationStatementNode> &declaration) const;

  void process_expression(
      const std::shared_ptr<ExpressionNode> &expression) const;

  [[nodiscard]] bool check_array_type(
      const std::shared_ptr<TypeNode> &type,
      const std::shared_ptr<TypeNode> &other) const;
  [[nodiscard]] static bool check_expression(
      const std::shared_ptr<ExpressionNode> &exp);

  [[nodiscard]] std::shared_ptr<TypeNode> infer_type(
      const std::shared_ptr<ExpressionNode> &node) const;
  [[nodiscard]] std::variant<std::nullptr_t, int, bool, char, float, Range,
                             std::shared_ptr<Array>>
  eval_value(const std::shared_ptr<ExpressionNode> &node) const;

  std::shared_ptr<ASTNode> root;
  std::vector<std::shared_ptr<SymbolScope>> scopes;
  const bool display{};
  bool in_control_flow{};
  SymbolType return_type{};
  std::unordered_map<std::string, std::shared_ptr<Symbol>>
      symbols_in_next_scope{};
};
}  // namespace carlos

#endif  // TABLE_H
