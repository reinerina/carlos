//
// Created by 陈洋 on 24-11-1.
//

#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <utility>
#include <variant>
#include <memory>
#include <vector>
#include <glog/logging.h>
#include "carlos.h"

namespace carlos {

class ASTNode;
class ExpressionNode;
class BinaryExpressionNode;
class UnaryExpressionNode;
class IdentifierExpressionNode;
class ConstantExpressionNode;
class CastExpressionNode;
class ArrayExpressionNode;
class ArrayAccessExpressionNode;
class StatementNode;
class DeclarationStatementNode;
class ExpressionStatementNode;
class StatementsNode;
class IfStatementNode;
class WhileStatementNode;
class ForStatementNode;
class TypeNode;
class BasicTypeNode;
class ArrayTypeNode;
class EntryNode;
class ProgramNode;
class ASTDisplay;

class ASTNode {
 public:
  virtual ~ASTNode() = default;
};

class TypeNode : public ASTNode {
 public:
  ~TypeNode() override = default;
};

class BasicTypeNode final : public TypeNode {
 public:
  ~BasicTypeNode() override = default;
  explicit BasicTypeNode(std::string type) : type(std::move(type)) {}

  std::string type;
};

class ExpressionNode : public ASTNode {
 public:
  ~ExpressionNode() override = default;

  // TODO: type of expression
  std::variant<std::nullptr_t, int, bool, char, float, Range,
               std::shared_ptr<Array>>
      value{};
};

class BinaryExpressionNode final : public ExpressionNode {
 public:
  ~BinaryExpressionNode() override = default;
  BinaryExpressionNode(std::shared_ptr<ExpressionNode> left, std::string op,
                       std::shared_ptr<ExpressionNode> right)
      : left(std::move(left)), right(std::move(right)), op(std::move(op)) {}

  std::shared_ptr<ExpressionNode> left, right;
  std::string op;
};

class UnaryExpressionNode final : public ExpressionNode {
 public:
  ~UnaryExpressionNode() override = default;
  UnaryExpressionNode(std::string op,
                      std::shared_ptr<ExpressionNode> expression)

      : expression(std::move(expression)), op(std::move(op)) {}

  std::shared_ptr<ExpressionNode> expression;
  std::string op;
};

class IdentifierExpressionNode final : public ExpressionNode {
 public:
  ~IdentifierExpressionNode() override = default;
  explicit IdentifierExpressionNode(std::string name) : name(std::move(name)) {}

  std::string name;
};

class ConstantExpressionNode final : public ExpressionNode {
 public:
  ~ConstantExpressionNode() override = default;
  template <typename T>
  explicit ConstantExpressionNode(T value) : ExpressionNode() {
    this->value = std::move(value);
  }
};

class CastExpressionNode final : public ExpressionNode {
 public:
  ~CastExpressionNode() override = default;
  CastExpressionNode(std::shared_ptr<ExpressionNode> expression,
                     std::shared_ptr<TypeNode> type)
      : expression(std::move(expression)), type(std::move(type)) {}

  std::shared_ptr<ExpressionNode> expression;
  std::shared_ptr<TypeNode> type;
};

class ArrayTypeNode final : public TypeNode {
 public:
  ~ArrayTypeNode() override = default;
  explicit ArrayTypeNode(const std::shared_ptr<Array> &array) {
    const auto res = build(array);
    CHECK_NE(res, nullptr) << "Array type is null";
    type = res;
    size = std::make_shared<ConstantExpressionNode>(array->size);
  }
  ArrayTypeNode(std::shared_ptr<TypeNode> type,
                std::shared_ptr<ExpressionNode> size)
      : type(std::move(type)), size(std::move(size)) {}

  std::shared_ptr<TypeNode> type;
  std::shared_ptr<ExpressionNode> size;

 private:
  static std::shared_ptr<TypeNode> build(const std::shared_ptr<Array> &array) {
    const auto size_expr =
        std::make_shared<ConstantExpressionNode>(array->size);

    if (const auto arr =
            std::get_if<std::shared_ptr<Array>>(&array->values[0])) {
      const auto inner = build(*arr);
      CHECK_NE(inner, nullptr) << "Inner array type is null";
      return std::make_shared<ArrayTypeNode>(inner, size_expr);
    }

    if (std::holds_alternative<int>(array->values[0])) {
      const auto basic_type = std::make_shared<BasicTypeNode>("i32");
      return std::make_shared<ArrayTypeNode>(basic_type, size_expr);
    }
    if (std::holds_alternative<float>(array->values[0])) {
      const auto basic_type = std::make_shared<BasicTypeNode>("f32");
      return std::make_shared<ArrayTypeNode>(basic_type, size_expr);
    }
    if (std::holds_alternative<bool>(array->values[0])) {
      const auto basic_type = std::make_shared<BasicTypeNode>("bool");
      return std::make_shared<ArrayTypeNode>(basic_type, size_expr);
    }
    if (std::holds_alternative<char>(array->values[0])) {
      const auto basic_type = std::make_shared<BasicTypeNode>("char");
      return std::make_shared<ArrayTypeNode>(basic_type, size_expr);
    }
    return nullptr;
  }
};

class ArrayExpressionNode final : public ExpressionNode {
 public:
  ~ArrayExpressionNode() override = default;
  explicit ArrayExpressionNode(const std::shared_ptr<TypeNode> &type) {
    const auto res = build(type);
    CHECK_NE(res, nullptr) << "Array type is null";
    element = res->element;
    count = res->count;
  }
  explicit ArrayExpressionNode(
      std::vector<std::shared_ptr<ExpressionNode>> elements)
      : elements(std::move(elements)) {}

  ArrayExpressionNode(std::shared_ptr<ExpressionNode> element,
                      std::shared_ptr<ExpressionNode> count)
      : element(std::move(element)), count(std::move(count)) {}

  std::vector<std::shared_ptr<ExpressionNode>> elements;
  std::shared_ptr<ExpressionNode> element, count;

 private:
  static std::shared_ptr<ArrayExpressionNode> build(
      const std::shared_ptr<TypeNode> &type) {
    if (const auto array_type =
            std::dynamic_pointer_cast<ArrayTypeNode>(type)) {
      const auto count = array_type->size;
      if (const auto child_array_type =
              std::dynamic_pointer_cast<ArrayTypeNode>(array_type->type)) {
        const auto inner = build(child_array_type);
        CHECK_NE(inner, nullptr) << "Inner array type is null";
        return std::make_shared<ArrayExpressionNode>(inner, count);
      }
      if (const auto basic_type =
              std::dynamic_pointer_cast<BasicTypeNode>(array_type->type)) {
        if (basic_type->type == "i32") {
          return std::make_shared<ArrayExpressionNode>(
              std::make_shared<ConstantExpressionNode>(0), count);
        }
        if (basic_type->type == "f32") {
          return std::make_shared<ArrayExpressionNode>(
              std::make_shared<ConstantExpressionNode>(0.0f), count);
        }
        if (basic_type->type == "bool") {
          return std::make_shared<ArrayExpressionNode>(
              std::make_shared<ConstantExpressionNode>(false), count);
        }
        if (basic_type->type == "char") {
          return std::make_shared<ArrayExpressionNode>(
              std::make_shared<ConstantExpressionNode>('\0'), count);
        }
        LOG(FATAL) << "Unknown basic type";
      }
    }
    return nullptr;
  }
};

class ArrayAccessExpressionNode final : public ExpressionNode {
 public:
  ~ArrayAccessExpressionNode() override = default;
  ArrayAccessExpressionNode(
      std::shared_ptr<IdentifierExpressionNode> array,
      std::vector<std::shared_ptr<ExpressionNode>> indices)
      : array(std::move(array)), indices(std::move(indices)) {}

  std::shared_ptr<IdentifierExpressionNode> array;
  std::vector<std::shared_ptr<ExpressionNode>> indices;
};

class RangeTypeNode final : public TypeNode {
 public:
  ~RangeTypeNode() override = default;
  RangeTypeNode(std::shared_ptr<ExpressionNode> start,
                std::shared_ptr<ExpressionNode> end, const bool inclusive)
      : start(std::move(start)), end(std::move(end)), inclusive(inclusive) {}

  std::shared_ptr<ExpressionNode> start;
  std::shared_ptr<ExpressionNode> end;
  bool inclusive;
};

class StatementNode : public ASTNode {
 public:
  ~StatementNode() override = default;
};

class DeclarationStatementNode final : public StatementNode {
 public:
  ~DeclarationStatementNode() override = default;

  DeclarationStatementNode(std::shared_ptr<IdentifierExpressionNode> identifier,
                           std::shared_ptr<TypeNode> type,
                           const bool mutability,
                           std::shared_ptr<ExpressionNode> expression)
      : identifier(std::move(identifier)),
        type(std::move(type)),
        mutability(mutability),
        expression(std::move(expression)) {
    if (this->expression == nullptr) {
      if (this->type == nullptr) {
        std::cerr << "DeclarationStatementNode: type and expression are null"
                  << std::endl;
      } else {
        if (const auto array_type =
                std::dynamic_pointer_cast<ArrayTypeNode>(this->type)) {
          if (array_type->size == nullptr) {
            std::cerr << "DeclarationStatementNode: array size is null"
                      << std::endl;
          } else {
            this->expression =
                std::make_shared<ArrayExpressionNode>(array_type);
          }

        } else if (const auto basic_type =
                       std::dynamic_pointer_cast<BasicTypeNode>(this->type)) {
          if (basic_type->type == "i32") {
            this->expression = std::make_shared<ConstantExpressionNode>(0);
          } else if (basic_type->type == "f32") {
            this->expression = std::make_shared<ConstantExpressionNode>(0.0f);
          } else if (basic_type->type == "bool") {
            this->expression = std::make_shared<ConstantExpressionNode>(false);
          } else if (basic_type->type == "char") {
            this->expression = std::make_shared<ConstantExpressionNode>('\0');
          } else {
            std::cerr << "DeclarationStatementNode: unknown type" << std::endl;
          }
        }
      }
    }
  }

  std::shared_ptr<IdentifierExpressionNode> identifier;
  std::shared_ptr<TypeNode> type;
  bool mutability;
  std::shared_ptr<ExpressionNode> expression;
};

class ExpressionStatementNode final : public StatementNode {
 public:
  ~ExpressionStatementNode() override = default;
  explicit ExpressionStatementNode(std::shared_ptr<ExpressionNode> expression)
      : expression(std::move(expression)) {}

  std::shared_ptr<ExpressionNode> expression;
};

class StatementsNode final : public StatementNode {
 public:
  ~StatementsNode() override = default;
  StatementsNode() {
    statements = std::vector<std::shared_ptr<StatementNode>>();
  }
  explicit StatementsNode(
      std::vector<std::shared_ptr<StatementNode>> statements)
      : statements(std::move(statements)) {}

  std::vector<std::shared_ptr<StatementNode>> statements;
};

class IfStatementNode final : public StatementNode {
 public:
  ~IfStatementNode() override = default;
  IfStatementNode(std::shared_ptr<ExpressionNode> condition,
                  std::shared_ptr<StatementNode> then_body,
                  std::shared_ptr<StatementNode> else_body)
      : condition(std::move(condition)),
        then_body(std::move(then_body)),
        else_body(std::move(else_body)) {}

  std::shared_ptr<ExpressionNode> condition;
  std::shared_ptr<StatementNode> then_body, else_body;
};

class WhileStatementNode final : public StatementNode {
 public:
  ~WhileStatementNode() override = default;
  WhileStatementNode(std::shared_ptr<ExpressionNode> condition,
                     std::shared_ptr<StatementNode> body)
      : condition(std::move(condition)), body(std::move(body)) {}

  std::shared_ptr<ExpressionNode> condition;
  std::shared_ptr<StatementNode> body;
};

class ForStatementNode final : public StatementNode {
 public:
  ~ForStatementNode() override = default;
  ForStatementNode(std::shared_ptr<IdentifierExpressionNode> iter,
                   const bool mutability,
                   std::shared_ptr<ExpressionNode> iterator,
                   std::shared_ptr<StatementNode> body)
      : iter(std::move(iter)),
        mutability(mutability),
        iterator(std::move(iterator)),
        body(std::move(body)) {}

  std::shared_ptr<IdentifierExpressionNode> iter;
  std::shared_ptr<ExpressionNode> iterator;
  std::shared_ptr<StatementNode> body;
  bool mutability{};
};

class ControlStatementNode final : public StatementNode {
 public:
  ~ControlStatementNode() override = default;
  explicit ControlStatementNode(std::string type) : type(std::move(type)) {}

  std::string type;
};

class ReturnStatementNode final : public StatementNode {
 public:
  explicit ReturnStatementNode(std::shared_ptr<ExpressionNode> expression)
      : expression(std::move(expression)) {}

  std::shared_ptr<ExpressionNode> expression;
};

class EntryNode final : public ASTNode {
 public:
  ~EntryNode() override = default;
  explicit EntryNode(std::shared_ptr<StatementsNode> statements)
      : statements(std::move(statements)) {}

  std::shared_ptr<StatementsNode> statements;
};

class ProgramNode final : public ASTNode {
 public:
  ~ProgramNode() override = default;
  explicit ProgramNode(std::shared_ptr<EntryNode> entry)
      : entry(std::move(entry)) {}

  std::shared_ptr<EntryNode> entry;
};

inline std::shared_ptr<ProgramNode> root = nullptr;

class ASTDisplay {
 public:
  explicit ASTDisplay(const std::shared_ptr<ASTNode> &root) : root(root) {}
  ASTDisplay(const std::shared_ptr<ASTNode> &root, const int step)
      : root(root), step(step) {
    CHECK_NE(root, nullptr) << "Root node is null";
    CHECK_NE(step, 0) << "Step is zero";
  }

  void print_ast(int indent = 0) const;

 private:
  void print_node(const std::shared_ptr<ASTNode> &node, int indent) const;

  static void print_indent(int indent);
  void print_type(const std::shared_ptr<TypeNode> &type, int indent) const;

  void print_expression(const std::shared_ptr<ExpressionNode> &expression,
                        int indent) const;

  void print_statement(const std::shared_ptr<StatementNode> &statement,
                       int indent) const;
  void print_entry(const std::shared_ptr<EntryNode> &entry, int indent) const;

  void print_program(const std::shared_ptr<ProgramNode> &program,
                     int indent) const;

  std::shared_ptr<ASTNode> root;
  int step = 2;
};
}  // namespace carlos

#endif  // AST_H