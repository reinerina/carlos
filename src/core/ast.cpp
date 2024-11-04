//
// Created by 陈洋 on 24-11-1.
//

#include "ast.h"

namespace carlos {
void ASTDisplay::print_ast(const int indent) const {
  const auto root_node = root;
  print_node(root_node, indent);
}

void ASTDisplay::print_node(const std::shared_ptr<ASTNode> &node,
                            const int indent) const {
  if (const auto program = std::dynamic_pointer_cast<ProgramNode>(node)) {
    print_program(program, indent);
  } else {
    LOG(FATAL) << "Unknown node type";
  }
}

void ASTDisplay::print_indent(const int indent) {
  for (auto i = 0; i < indent; i++) {
    std::cout << " ";
  }
}

void ASTDisplay::print_entry(const std::shared_ptr<EntryNode> &entry,
                             const int indent) const {
  print_indent(indent);
  std::cout << "Entry: " << std::endl;
  const auto statements = entry->statements;
  print_statement(statements, indent + step);
}

void ASTDisplay::print_program(const std::shared_ptr<ProgramNode> &program,
                               const int indent) const {
  print_indent(indent);
  std::cout << "Program: " << std::endl;
  const auto entry = program->entry;
  print_entry(entry, indent + step);
}

void ASTDisplay::print_statement(
    const std::shared_ptr<StatementNode> &statement, const int indent) const {
  if (statement == nullptr) {
    return;
  }
  if (const auto statements =
          std::dynamic_pointer_cast<StatementsNode>(statement)) {
    print_indent(indent);
    std::cout << "Statements: " << std::endl;
    for (const auto &stat : statements->statements) {
      print_statement(stat, indent + step);
    }
  } else if (const auto declaration =
                 std::dynamic_pointer_cast<DeclarationStatementNode>(
                     statement)) {
    print_indent(indent);
    std::cout << "Declaration: " << std::endl;
    print_indent(indent + step);
    std::cout << "Identifier: " << declaration->identifier->name << std::endl;
    print_type(declaration->type, indent + step);
    print_indent(indent + step);
    std::cout << "Mutable: " << std::boolalpha << declaration->mutability
              << std::endl;
    print_indent(indent + step);
    std::cout << "Expression: " << std::endl;
    print_expression(declaration->expression, indent + 2 * step);
  } else if (const auto expression =
                 std::dynamic_pointer_cast<ExpressionStatementNode>(
                     statement)) {
    print_indent(indent);
    std::cout << "Expression: " << std::endl;
    print_expression(expression->expression, indent + step);
  } else if (const auto if_stat =
                 std::dynamic_pointer_cast<IfStatementNode>(statement)) {
    if (if_stat->condition == nullptr) {
      if (if_stat->then_body == nullptr) {
        LOG(FATAL) << "Empty if statement";
      } else {
        print_statement(if_stat->then_body, indent);
      }
    } else {
      print_indent(indent);
      std::cout << "If: " << std::endl;
      print_indent(indent + step);
      std::cout << "Condition: " << std::endl;
      print_expression(if_stat->condition, indent + 2 * step);
      print_indent(indent + step);
      std::cout << "Then: " << std::endl;
      print_statement(if_stat->then_body, indent + 2 * step);
      if (if_stat->else_body != nullptr) {
        print_indent(indent + step);
        std::cout << "Else: " << std::endl;
        print_statement(if_stat->else_body, indent + 2 * step);
      }
    }
  } else if (const auto while_stat =
                 std::dynamic_pointer_cast<WhileStatementNode>(statement)) {
    print_indent(indent);
    std::cout << "While: " << std::endl;
    print_indent(indent + step);
    std::cout << "Condition: " << std::endl;
    print_expression(while_stat->condition, indent + 2 * step);
    print_statement(while_stat->body, indent + step);
  } else if (const auto for_stat =
                 std::dynamic_pointer_cast<ForStatementNode>(statement)) {
    print_indent(indent);
    std::cout << "For: " << std::endl;
    print_indent(indent + step);
    std::cout << "Iterator: " << std::endl;
    print_expression(for_stat->iter, indent + 2 * step);
    print_indent(indent + step);
    std::cout << "Range: " << std::endl;
    print_expression(for_stat->iterator, indent + 2 * step);
    print_statement(for_stat->body, indent + step);
  } else if (const auto return_stat =
                 std::dynamic_pointer_cast<ReturnStatementNode>(statement)) {
    print_indent(indent);
    if (return_stat->expression == nullptr) {
      std::cout << "Return" << std::endl;
    } else {
      std::cout << "Return: " << std::endl;
      print_expression(return_stat->expression, indent + step);
    }
  } else if (const auto control =
                 std::dynamic_pointer_cast<ControlStatementNode>(statement)) {
    if (control->type == "break") {
      print_indent(indent);
      std::cout << "Break" << std::endl;
    } else if (control->type == "continue") {
      print_indent(indent);
      std::cout << "Continue" << std::endl;
    } else {
      LOG(FATAL) << "Unknown control statement type";
    }
  } else if (const auto call =
                 std::dynamic_pointer_cast<CallStatementNode>(statement)) {
    print_indent(indent);
    std::cout << "Call: " << std::endl;
    print_indent(indent + step);
    std::cout << "Identifier: " << std::endl;
    print_indent(indent + 2 * step);
    std::cout << call->name << std::endl;
    print_indent(indent + step);
    std::cout << "Parameters: " << std::endl;
    for (const auto &param : call->expressions) {
      print_expression(param, indent + 2 * step);
    }
  } else {
    LOG(FATAL) << "Unknown statement type";
  }
}

void ASTDisplay::print_expression(
    const std::shared_ptr<ExpressionNode> &expression, const int indent) const {
  if (expression == nullptr) {
    return;
  }
  if (const auto constant =
          std::dynamic_pointer_cast<ConstantExpressionNode>(expression)) {
    print_indent(indent);
    if (std::holds_alternative<int>(constant->value)) {
      const auto value = std::get<int>(constant->value);
      std::cout << "Constant: " << value << std::endl;
    } else if (std::holds_alternative<float>(constant->value)) {
      const auto value = std::get<float>(constant->value);
      std::cout << "Constant: " << value << std::endl;
    } else if (std::holds_alternative<char>(constant->value)) {
      const auto value = std::get<char>(constant->value);
      std::cout << "Constant: " << value << std::endl;
    } else if (std::holds_alternative<bool>(constant->value)) {
      const auto value = std::get<bool>(constant->value);
      std::cout << "Constant: " << std::boolalpha << value << std::endl;
    } else {
      LOG(FATAL) << "Unknown constant type";
    }
  } else if (const auto identifier =
                 std::dynamic_pointer_cast<IdentifierExpressionNode>(
                     expression)) {
    print_indent(indent);
    std::cout << "Identifier: " << identifier->name << std::endl;
  } else if (const auto binary =
                 std::dynamic_pointer_cast<BinaryExpressionNode>(expression)) {
    print_indent(indent);
    std::cout << "Binary: " << std::endl;
    print_indent(indent + step);
    std::cout << "Operator: " << binary->op << std::endl;
    print_expression(binary->left, indent + step);
    print_expression(binary->right, indent + step);
  } else if (const auto unary =
                 std::dynamic_pointer_cast<UnaryExpressionNode>(expression)) {
    print_indent(indent);
    std::cout << "Unary: " << std::endl;
    print_indent(indent + step);
    std::cout << "Operator: " << unary->op << std::endl;
    print_expression(unary->expression, indent + step);
    print_indent(indent);
  } else if (const auto cast =
                 std::dynamic_pointer_cast<CastExpressionNode>(expression)) {
    print_indent(indent);
    std::cout << "Cast: " << std::endl;
    print_indent(indent + step);
    std::cout << "Type: " << std::endl;
    print_type(cast->type, indent + 2 * step);
    print_expression(cast->expression, indent + step);
  } else if (const auto array =
                 std::dynamic_pointer_cast<ArrayExpressionNode>(expression)) {
    if (array->element == nullptr || array->count == nullptr) {
      if (array->elements.empty()) {
        LOG(FATAL) << "Empty array";
      } else {
        print_indent(indent);
        std::cout << "Array: " << std::endl;
        for (const auto &element : array->elements) {
          print_expression(element, indent + step);
        }
      }
    } else {
      if (!array->elements.empty()) {
        LOG(FATAL) << "Array definition and initialization at the same time";
      } else {
        print_indent(indent);
        std::cout << "Array: " << std::endl;
        print_indent(indent + step);
        std::cout << "Element: " << std::endl;
        print_expression(array->element, indent + 2 * step);
        print_indent(indent + step);
        std::cout << "Count: " << std::endl;
        print_expression(array->count, indent + 2 * step);
      }
    }
  } else if (const auto array_access =
                 std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                     expression)) {
    print_indent(indent);
    std::cout << "Array Access: " << std::endl;
    print_indent(indent + step);
    std::cout << "Identifier: " << array_access->array->name << std::endl;
    print_indent(indent + step);
    std::cout << "Indices: " << std::endl;
    for (const auto &index : array_access->indices) {
      print_expression(index, indent + 2 * step);
    }
  } else {
    LOG(FATAL) << "Unknown expression type";
  }
}

void ASTDisplay::print_type(const std::shared_ptr<TypeNode> &type,
                            const int indent) const {
  if (type == nullptr) {
    return;
  }
  if (const auto array_type = std::dynamic_pointer_cast<ArrayTypeNode>(type)) {
    print_indent(indent);
    std::cout << "Array Type: " << std::endl;
    print_indent(indent + step);
    std::cout << "Size: " << std::endl;
    print_expression(array_type->size, indent + 2 * step);
    print_indent(indent + step);
    std::cout << "Type: " << std::endl;
    print_type(array_type->type, indent + 2 * step);
  } else if (const auto basic_type =
                 std::dynamic_pointer_cast<BasicTypeNode>(type)) {
    print_indent(indent);
    std::cout << "Basic Type: " << basic_type->type << std::endl;
  } else {
    LOG(FATAL) << "Unknown type";
  }
}

}  // namespace carlos
