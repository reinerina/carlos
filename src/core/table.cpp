//
// Created by 陈洋 on 24-11-2.
//

#include "table.h"

namespace carlos {
void SymbolTable::process_node(const std::shared_ptr<ASTNode> &node) {
  if (const auto program = std::dynamic_pointer_cast<ProgramNode>(node)) {
    process_program(program);
  } else {
    LOG(FATAL) << "Unknown node type";
  }
}

void SymbolTable::process_program(const std::shared_ptr<ProgramNode> &program) {
  process_entry(program->entry);
}

void SymbolTable::process_entry(const std::shared_ptr<EntryNode> &entry) {
  process_statement(entry->statements);
}

void SymbolTable::process_statement(
    const std::shared_ptr<StatementNode> &statement) {
  if (statement == nullptr) {
    return;
  }
  if (const auto statements =
          std::dynamic_pointer_cast<StatementsNode>(statement)) {
    enter_scope();
    for (const auto &stat : statements->statements) {
      process_statement(stat);
    }
    exit_scope();
  } else if (const auto declaration =
                 std::dynamic_pointer_cast<DeclarationStatementNode>(
                     statement)) {
    process_declaration(declaration);
  } else if (const auto expression =
                 std::dynamic_pointer_cast<ExpressionStatementNode>(
                     statement)) {
    process_expression(expression->expression);
  } else if (const auto if_stat =
                 std::dynamic_pointer_cast<IfStatementNode>(statement)) {
    if (if_stat->condition == nullptr) {
      CHECK_EQ(if_stat->else_body, nullptr) << "If condition is null, but else "
                                               "body is not null";

      in_control_flow = true;
      process_statement(if_stat->then_body);
      in_control_flow = false;
    } else {
      const auto condition_type = infer_type(if_stat->condition);
      if (condition_type == nullptr) {
        LOG(FATAL) << "If condition type is null";
        return;
      }
      if (const auto basic_type =
              std::dynamic_pointer_cast<BasicTypeNode>(condition_type)) {
        if (basic_type->type != "bool") {
          LOG(FATAL) << "If condition is not a boolean";
        } else {
          in_control_flow = true;
          process_statement(if_stat->then_body);
          in_control_flow = false;
          if (if_stat->else_body != nullptr) {
            in_control_flow = true;
            process_statement(if_stat->else_body);
            in_control_flow = false;
          }
        }
      } else {
        LOG(FATAL) << "Unknown condition type";
      }
    }
  } else if (const auto while_stat =
                 std::dynamic_pointer_cast<WhileStatementNode>(statement)) {
    const auto condition_type = infer_type(while_stat->condition);
    if (condition_type == nullptr) {
      LOG(FATAL) << "While condition type is null";
      return;
    }
    if (const auto basic_type =
            std::dynamic_pointer_cast<BasicTypeNode>(condition_type)) {
      if (basic_type->type != "bool") {
        LOG(FATAL) << "While condition is not a boolean";
      } else {
        in_control_flow = true;
        process_statement(while_stat->body);
        in_control_flow = false;
      }
    } else {
      LOG(FATAL) << "Unknown condition type";
    }
  } else if (const auto for_stat =
                 std::dynamic_pointer_cast<ForStatementNode>(statement)) {
    const auto iterator_type = infer_type(for_stat->iterator);
    const auto iterator_name = for_stat->iter->name;
    if (iterator_type == nullptr) {
      LOG(FATAL) << "For iterator type is null";
      return;
    }
    if (const auto range =
            std::dynamic_pointer_cast<RangeTypeNode>(iterator_type)) {
      // TODO: Check start and end value
      add_symbol_to_next_scope(iterator_name, SymbolType::INT,
                               SymbolKind::VARIABLE, for_stat->mutability);
      in_control_flow = true;
      process_statement(for_stat->body);
      in_control_flow = false;
    } else {
      LOG(FATAL) << "Unknown iterator type";
    }
  } else if (const auto control =
                 std::dynamic_pointer_cast<ControlStatementNode>(statement)) {
    if (!in_control_flow) {
      LOG(FATAL) << "Control statement outside of control flow";
    }
  } else if (const auto return_stat =
                 std::dynamic_pointer_cast<ReturnStatementNode>(statement)) {
    auto ret_ty = SymbolType::VOID;
    if (return_stat->expression != nullptr) {
      const auto ret_type = infer_type(return_stat->expression);
      if (const auto ret = std::static_pointer_cast<BasicTypeNode>(ret_type)) {
        if (ret->type == "i32") {
          ret_ty = SymbolType::INT;
        } else if (ret->type == "f32") {
          ret_ty = SymbolType::FLOAT;
        } else if (ret->type == "char") {
          ret_ty = SymbolType::CHAR;
        } else if (ret->type == "bool") {
          ret_ty = SymbolType::BOOL;
        } else {
          LOG(FATAL) << "Unknown return type";
        }
      }
    }
    if (const auto cur_scope = current_scope(); return_type != ret_ty) {
      LOG(FATAL) << "Return type mismatch";
    }
  } else {
    LOG(FATAL) << "Unknown statement type";
  }
}

void SymbolTable::process_declaration(
    const std::shared_ptr<DeclarationStatementNode> &declaration) const {
  const auto name = declaration->identifier->name;
  auto type = declaration->type;
  constexpr auto kind = SymbolKind::VARIABLE;
  const auto mutability = declaration->mutability;
  const auto expression = declaration->expression;
  if (type == nullptr) {
    type = infer_type(expression);
  } else {
    const auto inferred_type = infer_type(expression);
  }
  if (const auto array_type = std::dynamic_pointer_cast<ArrayTypeNode>(type)) {
    add_symbol(name, array_type, kind, mutability);
  } else if (const auto basic_type =
                 std::dynamic_pointer_cast<BasicTypeNode>(type)) {
    auto symbol_type = SymbolType::UNKNOWN;
    if (basic_type->type == "i32") {
      symbol_type = SymbolType::INT;
    } else if (basic_type->type == "f32") {
      symbol_type = SymbolType::FLOAT;
    } else if (basic_type->type == "char") {
      symbol_type = SymbolType::CHAR;
    } else if (basic_type->type == "bool") {
      symbol_type = SymbolType::BOOL;
    } else {
      LOG(FATAL) << "Unknown basic type";
    }
    add_symbol(name, symbol_type, kind, mutability);
  } else {
    LOG(FATAL) << "Unknown type";
  }
}

void SymbolTable::process_expression(
    const std::shared_ptr<ExpressionNode> &expression) const {
  const auto type = infer_type(expression);
}

std::shared_ptr<TypeNode> SymbolTable::infer_type(
    const std::shared_ptr<ExpressionNode> &node) const {
  if (node == nullptr) {
    return nullptr;
  }
  if (const auto constant =
          std::dynamic_pointer_cast<ConstantExpressionNode>(node)) {
    const auto value = &constant->value;
    if (std::holds_alternative<int>(*value)) {
      return std::make_shared<BasicTypeNode>("i32");
    }
    if (std::holds_alternative<float>(*value)) {
      return std::make_shared<BasicTypeNode>("f32");
    }
    if (std::holds_alternative<char>(*value)) {
      return std::make_shared<BasicTypeNode>("char");
    }
    if (std::holds_alternative<bool>(*value)) {
      return std::make_shared<BasicTypeNode>("bool");
    }
    LOG(FATAL) << "Unknown constant type";
    return nullptr;
  }
  if (const auto identifier =
          std::dynamic_pointer_cast<IdentifierExpressionNode>(node)) {
    if (const auto symbol = get_symbol(identifier->name)) {
      if (symbol->dimensions.empty()) {
        const auto symbol_type = symbol->type;
        if (symbol_type == SymbolType::INT) {
          return std::make_shared<BasicTypeNode>("i32");
        }
        if (symbol_type == SymbolType::FLOAT) {
          return std::make_shared<BasicTypeNode>("f32");
        }
        if (symbol_type == SymbolType::CHAR) {
          return std::make_shared<BasicTypeNode>("char");
        }
        if (symbol_type == SymbolType::BOOL) {
          return std::make_shared<BasicTypeNode>("bool");
        }
        LOG(FATAL) << "Unknown symbol type";
      } else {
        // TODO: Auto infer array type
      }
    }
    return nullptr;
  }
  if (const auto binary =
          std::dynamic_pointer_cast<BinaryExpressionNode>(node)) {
    const auto left = infer_type(binary->left);
    const auto right = infer_type(binary->right);
    const auto op = binary->op;
    if (const auto l_basic = std::dynamic_pointer_cast<BasicTypeNode>(left)) {
      if (const auto r_basic =
              std::dynamic_pointer_cast<BasicTypeNode>(right)) {
        if (l_basic->type == "i32" && r_basic->type == "i32") {
          if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%") {
            return std::make_shared<BasicTypeNode>("i32");
          }
          if (op == "<" || op == "<=" || op == ">" || op == ">=" ||
              op == "==" || op == "!=") {
            return std::make_shared<BasicTypeNode>("bool");
          }
          if (op == "..") {
            return std::make_shared<RangeTypeNode>(binary->left, binary->right,
                                                   false);
          }
          if (op == "..=") {
            return std::make_shared<RangeTypeNode>(binary->left, binary->right,
                                                   true);
          }
          if (op == "=" || "+=" || "-=" || "*=" || "/=" || "%=") {
            if (const auto identifier =
                    std::dynamic_pointer_cast<IdentifierExpressionNode>(
                        binary->left)) {
              const auto symbol = get_symbol(identifier->name);
              if (symbol == nullptr) {
                LOG(FATAL) << "Unknown symbol";
                return nullptr;
              }
              if (symbol->mutability) {
                return nullptr;
              }
              LOG(FATAL) << "Try to assign to immutable symbol";
              return nullptr;
            }
            if (const auto array_access =
                    std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                        binary->left)) {
              const auto symbol = get_symbol(array_access->array->name);
              if (symbol == nullptr) {
                LOG(FATAL) << "Unknown array";
                return nullptr;
              }
              if (symbol->mutability) {
                return std::make_shared<BasicTypeNode>("bool");
              }
              LOG(FATAL) << "Try to assign to immutable symbol";
              return nullptr;
            }
            LOG(FATAL) << "Try to assign to non-identifier";
            return nullptr;
          }
        }
        if (l_basic->type == "f32" && r_basic->type == "f32") {
          if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%") {
            return std::make_shared<BasicTypeNode>("f32");
          }
          if (op == "<" || op == "<=" || op == ">" || op == ">=" ||
              op == "==" || op == "!=") {
            return std::make_shared<BasicTypeNode>("bool");
          }
          if (op == "=" || "+=" || "-=" || "*=" || "/=" || "%=") {
            if (const auto identifier =
                    std::dynamic_pointer_cast<IdentifierExpressionNode>(
                        binary->left)) {
              const auto symbol = get_symbol(identifier->name);
              if (symbol == nullptr) {
                LOG(FATAL) << "Unknown symbol";
                return nullptr;
              }
              if (symbol->mutability) {
                return nullptr;
              }
              LOG(FATAL) << "Try to assign to immutable symbol";
              return nullptr;
            }
            if (const auto array_access =
                    std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                        binary->left)) {
              const auto symbol = get_symbol(array_access->array->name);
              if (symbol == nullptr) {
                LOG(FATAL) << "Unknown array";
                return nullptr;
              }
              if (symbol->mutability) {
                return std::make_shared<BasicTypeNode>("bool");
              }
              LOG(FATAL) << "Try to assign to immutable symbol";
              return nullptr;
            }
            LOG(FATAL) << "Try to assign to non-identifier";
            return nullptr;
          }
        }
        if (l_basic->type == "bool" && r_basic->type == "bool") {
          if (op == "&&" || op == "||") {
            return std::make_shared<BasicTypeNode>("bool");
          }
          if (op == "==" || op == "!=") {
            return std::make_shared<BasicTypeNode>("bool");
          }
          if (op == "=") {
            if (const auto identifier =
                    std::dynamic_pointer_cast<IdentifierExpressionNode>(
                        binary->left)) {
              const auto symbol = get_symbol(identifier->name);
              if (symbol == nullptr) {
                LOG(FATAL) << "Unknown symbol";
                return nullptr;
              }
              if (symbol->mutability) {
                return nullptr;
              }
              LOG(FATAL) << "Try to assign to immutable symbol";
              return nullptr;
            }
            if (const auto array_access =
                    std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                        binary->left)) {
              const auto symbol = get_symbol(array_access->array->name);
              if (symbol == nullptr) {
                LOG(FATAL) << "Unknown array";
                return nullptr;
              }
              if (symbol->mutability) {
                return std::make_shared<BasicTypeNode>("bool");
              }
              LOG(FATAL) << "Try to assign to immutable symbol";
              return nullptr;
            }
            LOG(FATAL) << "Try to assign to non-identifier";
            return nullptr;
          }
        }
        if (l_basic->type == "char" && r_basic->type == "char") {
          if (op == "<" || op == "<=" || op == ">" || op == ">=" ||
              op == "==" || op == "!=") {
            return std::make_shared<BasicTypeNode>("bool");
          }
          if (op == "=") {
            if (const auto identifier =
                    std::dynamic_pointer_cast<IdentifierExpressionNode>(
                        binary->left)) {
              const auto symbol = get_symbol(identifier->name);
              if (symbol == nullptr) {
                LOG(FATAL) << "Unknown symbol";
                return nullptr;
              }
              if (symbol->mutability) {
                return nullptr;
              }
              LOG(FATAL) << "Try to assign to immutable symbol";
              return nullptr;
            }
            if (const auto array_access =
                    std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                        binary->left)) {
              const auto symbol = get_symbol(array_access->array->name);
              if (symbol == nullptr) {
                LOG(FATAL) << "Unknown array";
                return nullptr;
              }
              if (symbol->mutability) {
                return std::make_shared<BasicTypeNode>("bool");
              }
              LOG(FATAL) << "Try to assign to immutable symbol";
              return nullptr;
            }
            LOG(FATAL) << "Try to assign to non-identifier";
            return nullptr;
          }
        }
        LOG(FATAL) << "Try to perform binary operation on different types";
        return nullptr;
      }
    }
    LOG(FATAL) << "Unknown binary type";
    return nullptr;
  }
  if (const auto unary = std::dynamic_pointer_cast<UnaryExpressionNode>(node)) {
    const auto exp = infer_type(unary->expression);
    if (const auto basic = std::dynamic_pointer_cast<BasicTypeNode>(exp)) {
      if (basic->type == "i32") {
        if (unary->op == "+" || unary->op == "-") {
          return std::make_shared<BasicTypeNode>("i32");
        }
      }
      if (basic->type == "f32") {
        if (unary->op == "+" || unary->op == "-") {
          return std::make_shared<BasicTypeNode>("f32");
        }
      }
      if (basic->type == "bool") {
        if (unary->op == "!") {
          return std::make_shared<BasicTypeNode>("bool");
        }
      }
      LOG(FATAL) << "Try to perform unary operation on invalid type";
      return nullptr;
    }
    LOG(FATAL) << "Unknown unary type";
    return nullptr;
  }
  if (const auto cast = std::dynamic_pointer_cast<CastExpressionNode>(node)) {
    auto type = cast->type;
    if (const auto basic = std::dynamic_pointer_cast<BasicTypeNode>(type)) {
      return type;
    }
    LOG(FATAL) << "Unknown cast type";
    return nullptr;
  }
  if (const auto array = std::dynamic_pointer_cast<ArrayExpressionNode>(node)) {
    if (array->elements.empty()) {
      if (array->element == nullptr || array->count == nullptr) {
        LOG(FATAL) << "Empty array";
        return nullptr;
      }
      const auto element_type = infer_type(array->element);
      const auto count_type = infer_type(array->count);
      if (const auto count_type_basic =
              std::dynamic_pointer_cast<BasicTypeNode>(count_type)) {
        if (count_type_basic->type == "i32") {
          return std::make_shared<ArrayTypeNode>(element_type, array->count);
        }
        LOG(FATAL) << "Array count is not an integer";
        return nullptr;
      }
      LOG(FATAL) << "Unknown count type";
      return nullptr;
    }
    const auto first_element = array->elements.front();
    const auto first_element_type = infer_type(first_element);
    for (const auto &element : array->elements) {
      const auto element_type = infer_type(element);
      if (const auto basic =
              std::dynamic_pointer_cast<BasicTypeNode>(element_type)) {
        if (const auto first_basic =
                std::dynamic_pointer_cast<BasicTypeNode>(first_element_type)) {
          if (first_basic->type != basic->type) {
            LOG(FATAL) << "Array elements have different types";
          }
        } else {
          LOG(FATAL) << "Unknown first element type";
        }
      } else if (const auto array_type =
                     std::dynamic_pointer_cast<ArrayTypeNode>(element_type)) {
        if (const auto first_array_type =
                std::dynamic_pointer_cast<ArrayTypeNode>(first_element_type)) {
          if (!check_array_type(first_array_type, array_type)) {
            // TODO: Check dimensions
            LOG(FATAL) << "Array elements have different types";
            return nullptr;
          }
        } else {
          LOG(FATAL) << "Unknown first element type";
          return nullptr;
        }
      } else {
        LOG(FATAL) << "Unknown element type";
        return nullptr;
      }
    }
    return std::make_shared<ArrayTypeNode>(
        first_element_type, std::make_shared<ConstantExpressionNode>(
                                static_cast<int>(array->elements.size())));
  }
  if (const auto array_access =
          std::dynamic_pointer_cast<ArrayAccessExpressionNode>(node)) {
    const auto symbol = get_symbol(array_access->array->name);
    if (symbol == nullptr) {
      LOG(FATAL) << "Unknown array";
      return nullptr;
    }
    if (symbol->dimensions.empty()) {
      LOG(FATAL) << "Try to access non-array";
      return nullptr;
    }
    if (symbol->dimensions.size() != array_access->indices.size()) {
      LOG(FATAL) << "Array access dimensions mismatch";
      return nullptr;
    }
    for (const auto &index : array_access->indices) {
      const auto index_type = infer_type(index);
      if (const auto index_type_basic =
              std::dynamic_pointer_cast<BasicTypeNode>(index_type)) {
        if (index_type_basic->type != "i32") {
          LOG(FATAL) << "Array access index is not an integer";
          return nullptr;
        }
      } else {
        LOG(FATAL) << "Unknown index type";
        return nullptr;
      }
    }
    if (symbol->type == SymbolType::INT) {
      return std::make_shared<BasicTypeNode>("i32");
    }
    if (symbol->type == SymbolType::FLOAT) {
      return std::make_shared<BasicTypeNode>("f32");
    }
    if (symbol->type == SymbolType::CHAR) {
      return std::make_shared<BasicTypeNode>("char");
    }
    if (symbol->type == SymbolType::BOOL) {
      return std::make_shared<BasicTypeNode>("bool");
    }
    LOG(FATAL) << "Unknown symbol type";
    return nullptr;
  }

  LOG(FATAL) << "Unknown expression type";
  return nullptr;
}

bool SymbolTable::check_array_type(const std::shared_ptr<TypeNode> &type,
                                   const std::shared_ptr<TypeNode> &other) {
  if (const auto array_type = std::dynamic_pointer_cast<ArrayTypeNode>(type)) {
    if (const auto other_array_type =
            std::dynamic_pointer_cast<ArrayTypeNode>(other)) {
      if (check_array_type(array_type->type, other_array_type->type)) {
        return true;
      }
      return false;
    }
    return false;
  }
  if (const auto basic_type = std::dynamic_pointer_cast<BasicTypeNode>(type)) {
    if (const auto other_basic_type =
            std::dynamic_pointer_cast<BasicTypeNode>(other)) {
      if (basic_type->type == other_basic_type->type) {
        return true;
      }
      return false;
    }
    return false;
  }
  return false;
}
}  // namespace carlos
