//
// Created by 陈洋 on 24-11-1.
//

#include <ast.h>

namespace carlos {
void AST::print_ast(const int indent) const {
  const auto root_node = root;
  print_node(root_node.get(), indent);
}

void AST::print_node(ASTNode *node, const int indent) const {
  if (const auto program = dynamic_cast<ProgramNode *>(node)) {
    print_program(program, indent);
  } else {
    std::cerr << "Unknown node type" << std::endl;
  }
}

void AST::print_indent(const int indent) {
  for (auto i = 0; i < indent; i++) {
    std::cout << " ";
  }
}

void AST::print_entry(const EntryNode *entry, const int indent) const {
  print_indent(indent);
  std::cout << "Entry: " << std::endl;
  const auto statements = entry->statements;
  print_statement(statements.get(), indent + step);
}

void AST::print_program(const ProgramNode *program, const int indent) const {
  print_indent(indent);
  std::cout << "Program: " << std::endl;
  auto entry = program->entry.get();
  print_entry(entry, indent + step);
}

void AST::print_statement(StatementNode *statement, const int indent) const {
  if (statement == nullptr) {
    return;
  }
  if (const auto statements = dynamic_cast<StatementsNode *>(statement)) {
    print_indent(indent);
    std::cout << "Statements: " << std::endl;
    for (const auto &stat : statements->statements) {
      print_statement(stat.get(), indent + step);
    }
  } else if (const auto declaration =
                 dynamic_cast<DeclarationStatementNode *>(statement)) {
    print_indent(indent);
    std::cout << "Declaration: " << std::endl;
    print_indent(indent + step);
    std::cout << "Identifier: " << declaration->identifier->name << std::endl;
    print_type(declaration->type.get(), indent + step);
    print_indent(indent + step);
    std::cout << "Mutable: " << std::boolalpha << declaration->mutability
              << std::endl;
    print_indent(indent + step);
    std::cout << "Expression: " << std::endl;
    print_expression(declaration->expression.get(), indent + 2 * step);
  } else if (const auto expression =
                 dynamic_cast<ExpressionStatementNode *>(statement)) {
    print_indent(indent);
    std::cout << "Expression: " << std::endl;
    print_expression(expression->expression.get(), indent + step);
  } else if (const auto if_stat = dynamic_cast<IfStatementNode *>(statement)) {
    if (if_stat->condition == nullptr) {
      if (if_stat->then_body == nullptr) {
        std::cerr << "Empty if statement" << std::endl;
      } else {
        print_statement(if_stat->then_body.get(), indent);
      }
    } else {
      print_indent(indent);
      std::cout << "If: " << std::endl;
      print_indent(indent + step);
      std::cout << "Condition: " << std::endl;
      print_expression(if_stat->condition.get(), indent + 2 * step);
      print_indent(indent + step);
      std::cout << "Then: " << std::endl;
      print_statement(if_stat->then_body.get(), indent + 2 * step);
      if (if_stat->else_body != nullptr) {
        print_indent(indent + step);
        std::cout << "Else: " << std::endl;
        print_statement(if_stat->else_body.get(), indent + 2 * step);
      }
    }
  } else if (const auto while_stat =
                 dynamic_cast<WhileStatementNode *>(statement)) {
    print_indent(indent);
    std::cout << "While: " << std::endl;
    print_indent(indent + step);
    std::cout << "Condition: " << std::endl;
    print_expression(while_stat->condition.get(), indent + 2 * step);
    print_statement(while_stat->body.get(), indent + step);
  } else if (const auto for_stat =
                 dynamic_cast<ForStatementNode *>(statement)) {
    print_indent(indent);
    std::cout << "For: " << std::endl;
    print_indent(indent + step);
    std::cout << "Iterator: " << std::endl;
    print_expression(for_stat->iter.get(), indent + 2 * step);
    print_indent(indent + step);
    std::cout << "Range: " << std::endl;
    print_expression(for_stat->iterator.get(), indent + 2 * step);
    print_statement(for_stat->body.get(), indent + step);
  } else if (const auto return_stat =
                 dynamic_cast<ReturnStatementNode *>(statement)) {
    print_indent(indent);
    if (return_stat->expression == nullptr) {
      std::cout << "Return" << std::endl;
    } else {
      std::cout << "Return: " << std::endl;
      print_expression(return_stat->expression.get(), indent + step);
    }
  } else if (const auto control =
                 dynamic_cast<ControlStatementNode *>(statement)) {
    if (control->type == "break") {
      print_indent(indent);
      std::cout << "Break" << std::endl;
    } else if (control->type == "continue") {
      print_indent(indent);
      std::cout << "Continue" << std::endl;
    } else {
      std::cerr << "Unknown control statement type" << std::endl;
    }
  } else {
    std::cerr << "Unknown statement type" << std::endl;
  }
}

void AST::print_expression(ExpressionNode *expression, const int indent) const {
  if (expression == nullptr) {
    return;
  }
  if (const auto constant =
          dynamic_cast<ConstantExpressionNode *>(expression)) {
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
      std::cerr << "Unknown constant type" << std::endl;
    }
  } else if (const auto identifier =
                 dynamic_cast<IdentifierExpressionNode *>(expression)) {
    print_indent(indent);
    std::cout << "Identifier: " << identifier->name << std::endl;
  } else if (const auto binary =
                 dynamic_cast<BinaryExpressionNode *>(expression)) {
    print_indent(indent);
    std::cout << "Binary: " << std::endl;
    print_indent(indent + step);
    std::cout << "Operator: " << binary->op << std::endl;
    print_expression(binary->left.get(), indent + step);
    print_expression(binary->right.get(), indent + step);
  } else if (const auto unary =
                 dynamic_cast<UnaryExpressionNode *>(expression)) {
    print_indent(indent);
    std::cout << "Unary: " << std::endl;
    print_indent(indent + step);
    std::cout << "Operator: " << unary->op << std::endl;
    print_expression(unary->expression.get(), indent + step);
    print_indent(indent);
  } else if (const auto cast = dynamic_cast<CastExpressionNode *>(expression)) {
    print_indent(indent);
    std::cout << "Cast: " << std::endl;
    print_indent(indent + step);
    std::cout << "Type: " << std::endl;
    print_type(cast->type.get(), indent + 2 * step);
    print_expression(cast->expression.get(), indent + step);
  } else if (const auto array =
                 dynamic_cast<ArrayExpressionNode *>(expression)) {
    if (array->element == nullptr || array->count == nullptr) {
      if (array->elements.empty()) {
        std::cerr << "Empty array" << std::endl;
      } else {
        print_indent(indent);
        std::cout << "Array: " << std::endl;
        for (const auto &element : array->elements) {
          print_expression(element.get(), indent + step);
        }
      }
    } else {
      if (!array->elements.empty()) {
        std::cerr << "Repeat definition" << std::endl;
      } else {
        print_indent(indent);
        std::cout << "Array: " << std::endl;
        print_indent(indent + step);
        std::cout << "Element: " << std::endl;
        print_expression(array->element.get(), indent + 2 * step);
        print_indent(indent + step);
        std::cout << "Count: " << std::endl;
        print_expression(array->count.get(), indent + 2 * step);
      }
    }
  } else if (const auto array_access =
                 dynamic_cast<ArrayAccessExpressionNode *>(expression)) {
    print_indent(indent);
    std::cout << "Array Access: " << std::endl;
    print_indent(indent + step);
    std::cout << "Identifier: " << array_access->array->name << std::endl;
    print_indent(indent + step);
    std::cout << "Indices: " << std::endl;
    for (const auto &index : array_access->indices) {
      print_expression(index.get(), indent + 2 * step);
    }
  } else {
    std::cerr << "Unknown expression type" << std::endl;
  }
}

void AST::print_type(TypeNode *type, const int indent) const {
  if (type == nullptr) {
    return;
  }
  if (const auto array_type = dynamic_cast<ArrayTypeNode *>(type)) {
    print_indent(indent);
    std::cout << "Array Type: " << std::endl;
    print_indent(indent + step);
    std::cout << "Size: " << std::endl;
    print_expression(array_type->size.get(), indent + 2 * step);
    print_indent(indent + step);
    std::cout << "Type: " << std::endl;
    print_type(array_type->type.get(), indent + 2 * step);
  } else if (const auto basic_type = dynamic_cast<BasicTypeNode *>(type)) {
    print_indent(indent);
    std::cout << "Basic Type: " << basic_type->type << std::endl;
  } else {
    std::cerr << "Unknown type" << std::endl;
  }
}

}  // namespace carlos
