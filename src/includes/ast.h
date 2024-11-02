//
// Created by 陈洋 on 24-11-1.
//

#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <glog/logging.h>

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
class AST;

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
  explicit ConstantExpressionNode(T value) : value(value) {}

  std::variant<int, float, bool, char> value;
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

class ArrayExpressionNode final : public ExpressionNode {
 public:
  ~ArrayExpressionNode() override = default;
  explicit ArrayExpressionNode(
      std::vector<std::shared_ptr<ExpressionNode>> elements)
      : elements(std::move(elements)) {}

  ArrayExpressionNode(std::shared_ptr<ExpressionNode> element,
                      std::shared_ptr<ExpressionNode> count)
      : element(std::move(element)), count(std::move(count)) {}

  std::vector<std::shared_ptr<ExpressionNode>> elements;
  std::shared_ptr<ExpressionNode> element, count;
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

class ArrayTypeNode final : public TypeNode {
 public:
  ~ArrayTypeNode() override = default;
  ArrayTypeNode(std::shared_ptr<TypeNode> type,
                std::shared_ptr<ExpressionNode> size)
      : type(std::move(type)), size(std::move(size)) {}

  std::shared_ptr<TypeNode> type;
  std::shared_ptr<ExpressionNode> size;
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
                dynamic_cast<ArrayTypeNode *>(this->type.get())) {
          if (array_type->size == nullptr) {
            std::cerr << "DeclarationStatementNode: array size is null"
                      << std::endl;
          }
          // TODO: array initialization
        } else if (const auto basic_type =
                       dynamic_cast<BasicTypeNode *>(this->type.get())) {
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
    // TODO: check type and expression, and auto type inference
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
                   std::shared_ptr<ExpressionNode> iterator,
                   std::shared_ptr<StatementNode> body)
      : iter(std::move(iter)),
        iterator(std::move(iterator)),
        body(std::move(body)) {}

  std::shared_ptr<IdentifierExpressionNode> iter;
  std::shared_ptr<ExpressionNode> iterator;
  std::shared_ptr<StatementNode> body;
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

class AST {
 public:
  explicit AST(const std::shared_ptr<ASTNode> &root) : root(root) {}
  AST(const std::shared_ptr<ProgramNode> &root, const int step)
      : root(root), step(step) {
    CHECK_NE(root, nullptr);
    CHECK_NE(step, 0);
  }

  void print_ast(int indent = 0) const;

  std::shared_ptr<ASTNode> root;
  int step = 2;

 private:
  void print_node(ASTNode *node, int indent) const;

  static void print_indent(int indent);
  void print_type(TypeNode *type, int indent) const;

  void print_expression(ExpressionNode *expression, int indent) const;

  void print_statement(StatementNode *statement, int indent) const;
  void print_entry(const EntryNode *entry, int indent) const;

  void print_program(const ProgramNode *program, int indent) const;
};
}  // namespace carlos

#endif  // AST_H