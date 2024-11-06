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

      const auto condition_value = eval_value(if_stat->condition);
      in_control_flow = true;
      process_statement(if_stat->then_body);
      in_control_flow = false;
    } else {
      const auto condition_type = infer_type(if_stat->condition);
      if (condition_type == nullptr) {
        LOG(FATAL) << "If condition type is null";
        return;
      }
      const auto condition_value = eval_value(if_stat->condition);
      if (const auto basic_type =
              std::dynamic_pointer_cast<BasicTypeNode>(condition_type)) {
        if (basic_type->type != "bool") {
          LOG(FATAL) << "If condition is not a boolean";
        } else {
          process_statement(if_stat->then_body);
          if (if_stat->else_body != nullptr) {
            process_statement(if_stat->else_body);
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
    const auto condition_value = eval_value(while_stat->condition);
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
    const auto iterator_value = eval_value(for_stat->iterator);
    if (const auto range =
            std::dynamic_pointer_cast<RangeTypeNode>(iterator_type)) {
      const auto start = eval_value(range->start);
      const auto end = eval_value(range->end);
      CHECK_EQ(std::holds_alternative<int>(start), true)
          << "Start value is not an integer";
      CHECK_EQ(std::holds_alternative<int>(end), true)
          << "End value is not an integer";
      const auto start_value = std::get<int>(start);
      for_stat->iter->value = start;

      add_symbol_to_next_scope(iterator_name, {start_value},
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
      const auto ret_value = eval_value(return_stat->expression);
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
  const auto type = declaration->type;
  constexpr auto kind = SymbolKind::VARIABLE;
  const auto mutability = declaration->mutability;
  const auto expression = declaration->expression;
  const auto inferred_type = infer_type(expression);
  if (const auto range_type =
          std::dynamic_pointer_cast<RangeTypeNode>(inferred_type)) {
    LOG(FATAL) << "Range type is not allowed in declaration";
  }
  if (type != nullptr) {
    if (const auto basic_type =
            std::dynamic_pointer_cast<BasicTypeNode>(type)) {
      if (const auto basic_inferred_type =
              std::dynamic_pointer_cast<BasicTypeNode>(inferred_type)) {
        if (basic_type->type != basic_inferred_type->type) {
          LOG(FATAL) << "Declaration type mismatch";
        }
      } else {
        LOG(FATAL) << "Declaration type mismatch";
      }
    }
    if (const auto array_type =
            std::dynamic_pointer_cast<ArrayTypeNode>(type)) {
      if (const auto array_inferred_type =
              std::dynamic_pointer_cast<ArrayTypeNode>(inferred_type)) {
        if (!check_array_type(array_type, array_inferred_type)) {
          LOG(FATAL) << "Declaration type mismatch";
        }
      } else {
        LOG(FATAL) << "Declaration type mismatch";
      }
    }
  } else {
    declaration->type = inferred_type;
  }
  const auto value = eval_value(expression);
  declaration->identifier->value = value;
  add_symbol(name, value, kind, mutability);
}

void SymbolTable::process_expression(
    const std::shared_ptr<ExpressionNode> &expression) const {
  const auto type = infer_type(expression);
  const auto value = eval_value(expression);
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
      const auto ty = std::make_shared<BasicTypeNode>("i32");
      constant->type = ty;
      return ty;
    }
    if (std::holds_alternative<float>(*value)) {
      const auto ty = std::make_shared<BasicTypeNode>("f32");
      constant->type = ty;
      return ty;
    }
    if (std::holds_alternative<char>(*value)) {
      const auto ty = std::make_shared<BasicTypeNode>("char");
      constant->type = ty;
      return ty;
    }
    if (std::holds_alternative<bool>(*value)) {
      const auto ty = std::make_shared<BasicTypeNode>("bool");
      constant->type = ty;
      return ty;
    }
    LOG(FATAL) << "Unknown constant type";
    return nullptr;
  }
  if (const auto identifier =
          std::dynamic_pointer_cast<IdentifierExpressionNode>(node)) {
    if (const auto symbol = get_symbol(identifier->name)) {
      const auto &value = symbol->value;
      if (std::holds_alternative<int>(value)) {
        const auto ty = std::make_shared<BasicTypeNode>("i32");
        identifier->type = ty;
        return ty;
      }
      if (std::holds_alternative<float>(value)) {
        const auto ty = std::make_shared<BasicTypeNode>("f32");
        identifier->type = ty;
        return ty;
      }
      if (std::holds_alternative<char>(value)) {
        const auto ty = std::make_shared<BasicTypeNode>("char");
        identifier->type = ty;
        return ty;
      }
      if (std::holds_alternative<bool>(value)) {
        const auto ty = std::make_shared<BasicTypeNode>("bool");
        identifier->type = ty;
        return ty;
      }
      if (std::holds_alternative<Range>(value)) {
        const auto range = std::get<Range>(value);

        const auto ty = std::make_shared<RangeTypeNode>(
            std::make_shared<ConstantExpressionNode>(range.start),
            std::make_shared<ConstantExpressionNode>(range.end),
            range.inclusive);
        identifier->type = ty;
        return ty;
      }
      if (std::holds_alternative<std::shared_ptr<Array>>(value)) {
        const auto array = std::get<std::shared_ptr<Array>>(value);
        const auto ty = std::make_shared<ArrayTypeNode>(array);
        identifier->type = ty;
        return ty;
      }
      LOG(FATAL) << "Unknown symbol type";
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
            const auto ty = std::make_shared<BasicTypeNode>("i32");
            binary->type = ty;
            return ty;
          }
          if (op == "<" || op == "<=" || op == ">" || op == ">=" ||
              op == "==" || op == "!=") {
            const auto ty = std::make_shared<BasicTypeNode>("bool");
            binary->type = ty;
            return ty;
          }
          if (op == "..") {
            const auto ty = std::make_shared<RangeTypeNode>(
                binary->left, binary->right, false);
            binary->type = ty;
            return ty;
          }
          if (op == "..=") {
            const auto ty = std::make_shared<RangeTypeNode>(
                binary->left, binary->right, true);
            binary->type = ty;
            return ty;
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
                return nullptr;
              }
              LOG(FATAL) << "Try to assign to immutable symbol";
              return nullptr;
            }
            LOG(FATAL) << "Try to assign to non-identifier";
            return nullptr;
          }
        }
        if (l_basic->type == "f32" && r_basic->type == "f32") {
          if (op == "+" || op == "-" || op == "*" || op == "/") {
            const auto ty = std::make_shared<BasicTypeNode>("f32");
            binary->type = ty;
            return ty;
          }
          if (op == "<" || op == "<=" || op == ">" || op == ">=" ||
              op == "==" || op == "!=") {
            const auto ty = std::make_shared<BasicTypeNode>("bool");
            binary->type = ty;
            return ty;
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
                return nullptr;
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
            const auto ty = std::make_shared<BasicTypeNode>("bool");
            binary->type = ty;
            return ty;
          }
          if (op == "==" || op == "!=") {
            const auto ty = std::make_shared<BasicTypeNode>("bool");
            binary->type = ty;
            return ty;
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
                return nullptr;
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
            const auto ty = std::make_shared<BasicTypeNode>("bool");
            binary->type = ty;
            return ty;
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
                return nullptr;
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
          const auto ty = std::make_shared<BasicTypeNode>("i32");
          unary->type = ty;
          return ty;
        }
      }
      if (basic->type == "f32") {
        if (unary->op == "+" || unary->op == "-") {
          const auto ty = std::make_shared<BasicTypeNode>("f32");
          unary->type = ty;
          return ty;
        }
      }
      if (basic->type == "bool") {
        if (unary->op == "!") {
          const auto ty = std::make_shared<BasicTypeNode>("bool");
          unary->type = ty;
          return ty;
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
        LOG(FATAL) << "Array is not declared properly";
        return nullptr;
      }
      const auto element_type = infer_type(array->element);
      const auto count_type = infer_type(array->count);
      if (const auto count_type_basic =
              std::dynamic_pointer_cast<BasicTypeNode>(count_type)) {
        if (count_type_basic->type == "i32") {
          const auto ty =
              std::make_shared<ArrayTypeNode>(element_type, array->count);
          array->type = ty;
          return ty;
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
    const auto ty = std::make_shared<ArrayTypeNode>(
        first_element_type, std::make_shared<ConstantExpressionNode>(
                                static_cast<int>(array->elements.size())));
    array->type = ty;
    return ty;
  }
  if (const auto array_access =
          std::dynamic_pointer_cast<ArrayAccessExpressionNode>(node)) {
    const auto symbol = get_symbol(array_access->array->name);
    if (symbol == nullptr) {
      LOG(FATAL) << "Unknown array";
      return nullptr;
    }
    if (!std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
      LOG(FATAL) << "Try to access non-array";
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
    const auto dimensions =
        std::get<std::shared_ptr<Array>>(symbol->value)->dimensions();
    if (dimensions.size() != array_access->indices.size()) {
      LOG(FATAL) << "Array access dimension mismatch";
      return nullptr;
    }
    if (symbol->type == SymbolType::INT) {
      const auto ty = std::make_shared<BasicTypeNode>("i32");
      array_access->type = ty;
      return ty;
    }
    if (symbol->type == SymbolType::FLOAT) {
      const auto ty = std::make_shared<BasicTypeNode>("f32");
      array_access->type = ty;
      return ty;
    }
    if (symbol->type == SymbolType::CHAR) {
      const auto ty = std::make_shared<BasicTypeNode>("char");
      array_access->type = ty;
      return ty;
    }
    if (symbol->type == SymbolType::BOOL) {
      const auto ty = std::make_shared<BasicTypeNode>("bool");
      array_access->type = ty;
      return ty;
    }
    LOG(FATAL) << "Unknown symbol type";
    return nullptr;
  }
  if (const auto call = std::dynamic_pointer_cast<CallExpressionNode>(node)) {
    if (call->name == "stdin") {
      for (const auto &exp : call->expressions) {
        if (const auto id =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(exp)) {
          const auto type = infer_type(exp);
          if (const auto basic =
                  std::dynamic_pointer_cast<BasicTypeNode>(type)) {
            if (basic->type != "i32" && basic->type != "f32" &&
                basic->type != "char" && basic->type != "bool") {
              LOG(FATAL) << "Stdin type is not a basic type";
            }
          } else {
            LOG(FATAL) << "Stdin type is not a basic type";
          }
          if (const auto value = eval_value(exp);
              std::holds_alternative<std::nullptr_t>(value)) {
            LOG(FATAL) << "Stdin value is null";
          }
          if (auto symbol = get_symbol(id->name); !symbol->mutability) {
            LOG(FATAL) << "Try to assign to immutable symbol";
          }
        } else if (const auto ac =
                       std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                           exp)) {
          const auto type = infer_type(exp);
          const auto symbol = get_symbol(ac->array->name);
          if (symbol->mutability == false) {
            LOG(FATAL) << "Try to assign to immutable symbol";
          }
          if (symbol->type != SymbolType::INT &&
              symbol->type != SymbolType::FLOAT &&
              symbol->type != SymbolType::CHAR &&
              symbol->type != SymbolType::BOOL) {
            LOG(FATAL) << "Unknown stdin type";
          }

        } else {
          LOG(FATAL) << "Call stdin with non-identifier";
        }
      }
      const auto ty = std::make_shared<BasicTypeNode>("i32");
      call->type = ty;
      return ty;
    }
    if (call->name == "stdout") {
      for (const auto &exp : call->expressions) {
        const auto type = infer_type(exp);
        if (const auto basic = std::dynamic_pointer_cast<BasicTypeNode>(type)) {
          if (basic->type != "i32" && basic->type != "f32" &&
              basic->type != "char" && basic->type != "bool") {
            LOG(FATAL) << "Unknown stdout type";
          }
        } else {
          LOG(FATAL) << "Unknown stdout type";
        }
        const auto value = eval_value(exp);
        if (std::holds_alternative<std::nullptr_t>(value)) {
          LOG(FATAL) << "Unknown stdout value";
        }
      }
      const auto ty = std::make_shared<BasicTypeNode>("i32");
      call->type = ty;
      return ty;
    }
    LOG(FATAL) << "Unknown call statement";
    return nullptr;
  }

  LOG(FATAL) << "Unknown expression type";
  return nullptr;
}
std::variant<std::nullptr_t, int, bool, char, float, Range,
             std::shared_ptr<Array>>
SymbolTable::eval_value(const std::shared_ptr<ExpressionNode> &node) const {
  if (node == nullptr) {
    return {};
  }

  if (const auto constant =
          std::dynamic_pointer_cast<ConstantExpressionNode>(node)) {
    return constant->value;
  }
  if (const auto identifier =
          std::dynamic_pointer_cast<IdentifierExpressionNode>(node)) {
    const auto symbol = get_symbol(identifier->name);
    if (symbol == nullptr) {
      LOG(FATAL) << "Unknown symbol";
      return {};
    }
    identifier->value = symbol->value;

    return symbol->value;
  }
  if (const auto binary =
          std::dynamic_pointer_cast<BinaryExpressionNode>(node)) {
    const auto left = eval_value(binary->left);
    const auto right = eval_value(binary->right);
    const auto op = binary->op;
    if (std::holds_alternative<std::nullptr_t>(left) &&
        std::holds_alternative<std::nullptr_t>(right)) {
      return {};
    }
    if (std::holds_alternative<int>(left) &&
        std::holds_alternative<int>(right)) {
      auto l = std::get<int>(left);
      const auto r = std::get<int>(right);
      if (op == "+") {
        const auto res = l + r;
        binary->value = res;
        return {res};
      }
      if (op == "-") {
        const auto res = l - r;
        binary->value = res;
        return {res};
      }
      if (op == "*") {
        const auto res = l * r;
        binary->value = res;
        return {res};
      }
      if (op == "/") {
        const auto res = l / r;
        binary->value = res;
        return {res};
      }
      if (op == "%") {
        const auto res = l % r;
        binary->value = res;
        return {res};
      }
      if (op == "<") {
        const auto res = l < r;
        binary->value = res;
        return {res};
      }
      if (op == "<=") {
        const auto res = l <= r;
        binary->value = res;
        return {res};
      }
      if (op == ">") {
        const auto res = l > r;
        binary->value = res;
        return {res};
      }
      if (op == ">=") {
        const auto res = l >= r;
        binary->value = res;
        return {res};
      }
      if (op == "==") {
        const auto res = l == r;
        binary->value = res;
        return {res};
      }
      if (op == "!=") {
        const auto res = l != r;
        binary->value = res;
        return {res};
      }
      if (op == "..") {
        const auto res = Range{l, r, false};
        binary->value = res;
        binary->is_constant = false;
        return {res};
      }
      if (op == "..=") {
        const auto res = Range{l, r, true};
        binary->value = res;
        binary->is_constant = false;
        return {res};
      }
      if (op == "=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l = r;
          l_identifier->value = l;
          symbol->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l = r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      if (op == "+=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l += r;
          l_identifier->value = l;
          symbol->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l += r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      if (op == "-=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l -= r;
          l_identifier->value = l;
          symbol->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l -= r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      if (op == "*=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l *= r;
          l_identifier->value = l;
          symbol->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l *= r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      if (op == "/=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l /= r;
          l_identifier->value = l;
          symbol->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l /= r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      if (op == "%=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l %= r;
          l_identifier->value = l;
          symbol->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l %= r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      return {};
    }
    if (std::holds_alternative<float>(left) &&
        std::holds_alternative<float>(right)) {
      auto l = std::get<float>(left);
      const auto r = std::get<float>(right);
      if (op == "+") {
        const auto res = l + r;
        binary->value = res;
        return {res};
      }
      if (op == "-") {
        const auto res = l - r;
        binary->value = res;
        return {res};
      }
      if (op == "*") {
        const auto res = l * r;
        binary->value = res;
        return {res};
      }
      if (op == "/") {
        const auto res = l / r;
        binary->value = res;
        return {res};
      }

      if (op == "<") {
        const auto res = l < r;
        binary->value = res;
        return {res};
      }
      if (op == "<=") {
        const auto res = l <= r;
        binary->value = res;
        return {res};
      }
      if (op == ">") {
        const auto res = l > r;
        binary->value = res;
        return {res};
      }
      if (op == ">=") {
        const auto res = l >= r;
        binary->value = res;
        return {res};
      }
      if (op == "==") {
        const auto res = l == r;
        binary->value = res;
        return {res};
      }
      if (op == "!=") {
        const auto res = l != r;
        binary->value = res;
        return {res};
      }
      if (op == "=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          l = r;
          l_identifier->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l = r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      if (op == "+=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l += r;
          l_identifier->value = l;
          symbol->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l += r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      if (op == "-=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l -= r;
          l_identifier->value = l;
          symbol->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l -= r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      if (op == "*=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l *= r;
          l_identifier->value = l;
          symbol->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l *= r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      if (op == "/=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l /= r;
          l_identifier->value = l;
          symbol->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l /= r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      LOG(FATAL) << "Cannot perform binary operation on float";
      return {};
    }
    if (std::holds_alternative<bool>(left) &&
        std::holds_alternative<bool>(right)) {
      auto l = std::get<bool>(left);
      const auto r = std::get<bool>(right);
      if (op == "&&") {
        const auto res = l && r;
        binary->value = res;
        return {res};
      }
      if (op == "||") {
        const auto res = l || r;
        binary->value = res;
        return {res};
      }
      if (op == "==") {
        const auto res = l == r;
        binary->value = res;
        return {res};
      }
      if (op == "!=") {
        const auto res = l != r;
        binary->value = res;
        return {res};
      }
      if (op == "=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l = r;
          l_identifier->value = l;
          symbol->value = l;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(array_access->array->name);
          l = r;
          array_access->value = l;
          if (std::holds_alternative<std::shared_ptr<Array>>(symbol->value)) {
            auto array = std::get<std::shared_ptr<Array>>(symbol->value);
            auto indices = std::vector<int>{};
            for (const auto &index : array_access->indices) {
              if (const auto index_value = eval_value(index);
                  std::holds_alternative<int>(index_value)) {
                indices.push_back(std::get<int>(index_value));
              } else {
                LOG(FATAL) << "Array index is not an integer";
                return {};
              }
            }
            array->set(indices, {l});
          }
        }
        return {};
      }
      return {};
    }
    if (std::holds_alternative<char>(left) &&
        std::holds_alternative<char>(right)) {
      auto l = std::get<char>(left);
      const auto r = std::get<char>(right);
      if (op == "<") {
        const auto res = l < r;
        binary->value = res;
        return {res};
      }
      if (op == "<=") {
        const auto res = l <= r;
        binary->value = res;
        return {res};
      }
      if (op == ">") {
        const auto res = l > r;
        binary->value = res;
        return {res};
      }
      if (op == ">=") {
        const auto res = l >= r;
        binary->value = res;
        return {res};
      }
      if (op == "==") {
        const auto res = l == r;
        binary->value = res;
        return {res};
      }
      if (op == "!=") {
        const auto res = l != r;
        binary->value = res;
        return {res};
      }
      if (op == "=") {
        if (const auto l_identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          auto symbol = get_symbol(l_identifier->name);
          l = r;
          l_identifier->value = l;
          symbol->value = l;
        }
        return {};
      }
      return {};
    }
  }

  if (const auto unary = std::dynamic_pointer_cast<UnaryExpressionNode>(node)) {
    const auto exp = eval_value(unary->expression);
    if (std::holds_alternative<std::nullptr_t>(exp)) {
      return {};
    }
    if (std::holds_alternative<int>(exp)) {
      const auto e = std::get<int>(exp);
      if (unary->op == "+") {
        const auto res = e;
        unary->value = res;
        return {res};
      }
      if (unary->op == "-") {
        const auto res = -e;
        unary->value = res;
        return {res};
      }
      return {};
    }
    if (std::holds_alternative<float>(exp)) {
      const auto e = std::get<float>(exp);
      if (unary->op == "+") {
        const auto res = e;
        unary->value = res;
        return {res};
      }
      if (unary->op == "-") {
        const auto res = -e;
        unary->value = res;
        return {res};
      }
      return {};
    }
    if (std::holds_alternative<bool>(exp)) {
      const auto e = std::get<bool>(exp);
      if (unary->op == "!") {
        const auto res = !e;
        unary->value = res;
        return {res};
      }
      return {};
    }
  }
  if (const auto cast = std::dynamic_pointer_cast<CastExpressionNode>(node)) {
    const auto type = cast->type;
    const auto value = eval_value(cast->expression);
    if (std::holds_alternative<std::nullptr_t>(value)) {
      return {};
    }
    if (std::holds_alternative<int>(value)) {
      const auto v = std::get<int>(value);
      if (const auto basic = std::dynamic_pointer_cast<BasicTypeNode>(type)) {
        if (basic->type == "i32") {
          const auto res = v;
          cast->value = res;
          return {res};
        }
        if (basic->type == "f32") {
          const auto res = static_cast<float>(v);
          cast->value = res;
          return {res};
        }
        if (basic->type == "char") {
          const auto res = static_cast<char>(v);
          cast->value = res;
          return {res};
        }
        if (basic->type == "bool") {
          const auto res = static_cast<bool>(v);
          cast->value = res;
          return {res};
        }
        LOG(FATAL) << "Unknown cast type";
        return {};
      }
      LOG(FATAL) << "Unknown cast type";
      return {};
    }
    if (std::holds_alternative<float>(value)) {
      const auto v = std::get<float>(value);
      if (const auto basic = std::dynamic_pointer_cast<BasicTypeNode>(type)) {
        if (basic->type == "i32") {
          const auto res = static_cast<int>(v);
          cast->value = res;
          return {res};
        }
        if (basic->type == " f32") {
          const auto res = v;
          cast->value = res;
          return {res};
        }
        if (basic->type == "char") {
          const auto res = static_cast<char>(v);
          cast->value = res;
          return {res};
        }
        if (basic->type == "bool") {
          const auto res = static_cast<bool>(v);
          cast->value = res;
          return {res};
        }
        LOG(FATAL) << "Unknown cast type";
        return {};
      }
    }
    if (std::holds_alternative<char>(value)) {
      const auto v = std::get<char>(value);
      if (const auto basic = std::dynamic_pointer_cast<BasicTypeNode>(type)) {
        if (basic->type == "i32") {
          const auto res = static_cast<int>(v);
          cast->value = res;
          return {res};
        }
        if (basic->type == "f32") {
          const auto res = static_cast<float>(v);
          cast->value = res;
          return {res};
        }
        if (basic->type == "char") {
          const auto res = v;
          cast->value = res;
          return {res};
        }
        if (basic->type == "bool") {
          const auto res = static_cast<bool>(v);
          cast->value = res;
          return {res};
        }
        LOG(FATAL) << "Unknown cast type";
        return {};
      }
    }
    if (std::holds_alternative<bool>(value)) {
      const auto v = std::get<bool>(value);
      if (const auto basic = std::dynamic_pointer_cast<BasicTypeNode>(type)) {
        if (basic->type == "i32") {
          const auto res = static_cast<int>(v);
          cast->value = res;
          return {res};
        }
        if (basic->type == "f32") {
          const auto res = static_cast<float>(v);
          cast->value = res;
          return {res};
        }
        if (basic->type == "char") {
          const auto res = static_cast<char>(v);
          cast->value = res;
          return {res};
        }
        if (basic->type == "bool") {
          const auto res = v;
          cast->value = res;
          return {res};
        }
        LOG(FATAL) << "Unknown cast type";
        return {};
      }
    }
    LOG(FATAL) << "Unknown cast type";
    return {};
  }
  if (const auto array = std::dynamic_pointer_cast<ArrayExpressionNode>(node)) {
    if (array->elements.empty()) {
      if (array->element == nullptr || array->count == nullptr) {
        LOG(FATAL) << "Empty array";
        return {};
      }
      if (!check_expression(array->count)) {
        LOG(FATAL) << "Array count is not a constant";
        return {};
      }
      const auto element = eval_value(array->element);
      const auto count = eval_value(array->count);
      if (std::holds_alternative<std::nullptr_t>(element) ||
          std::holds_alternative<std::nullptr_t>(count)) {
        return {};
      }
      if (std::holds_alternative<int>(count)) {
        const auto c = std::get<int>(count);
        auto elements =
            std::vector<std::variant<std::nullptr_t, int, bool, char, float,
                                     Range, std::shared_ptr<Array>>>{};
        for (auto i = 0; i < c; ++i) {
          elements.push_back(element);
        }
        const auto res = std::make_shared<Array>(c, elements);
        array->value = res;
        return {res};
      }
      LOG(FATAL) << "Array count is not an integer";
      return {};
    }
    auto elements =
        std::vector<std::variant<std::nullptr_t, int, bool, char, float, Range,
                                 std::shared_ptr<Array>>>{};
    for (const auto &element : array->elements) {
      const auto value = eval_value(element);
      if (std::holds_alternative<std::nullptr_t>(value)) {
        return {};
      }
      elements.push_back(value);
    }
    const auto res = std::make_shared<Array>(elements.size(), elements);
    array->value = res;
    return {res};
  }
  if (const auto array_access =
          std::dynamic_pointer_cast<ArrayAccessExpressionNode>(node)) {
    const auto symbol = get_symbol(array_access->array->name);
    if (symbol == nullptr) {
      LOG(FATAL) << "Unknown array";
      return {};
    }
    array_access->array->value = symbol->value;
    if (std::holds_alternative<std::shared_ptr<Array>>(
            array_access->array->value)) {
      const auto array =
          std::get<std::shared_ptr<Array>>(array_access->array->value);
      const auto dimensions = array->dimensions();
      if (array_access->indices.size() != dimensions.size()) {
        LOG(FATAL) << "Array access dimensions mismatch";
        return {};
      }
      auto indices = std::vector<int>{};
      for (const auto &index : array_access->indices) {
        const auto value = eval_value(index);
        if (std::holds_alternative<std::nullptr_t>(value)) {
          LOG(FATAL) << "Array access index cannot be evaluated";
          return {};
        }
        if (std::holds_alternative<int>(value)) {
          indices.push_back(std::get<int>(value));
        } else {
          LOG(FATAL) << "Array access index is not an integer";
          return {};
        }
      }
      if (indices.size() != dimensions.size()) {
        LOG(FATAL) << "Array access dimensions mismatch";
        return {};
      }
      auto value = array->get(indices);
      if (std::holds_alternative<std::nullptr_t>(value)) {
        return {};
      }
      array_access->value = value;
      return value;
    }
    LOG(FATAL) << "Try to access non-array";
    return {};
  }
  if (const auto call = std::dynamic_pointer_cast<CallExpressionNode>(node)) {
    if (call->name == "stdin") {
      for (const auto &exp : call->expressions) {
        const auto value = eval_value(exp);
        if (std::holds_alternative<std::nullptr_t>(value)) {
          LOG(FATAL) << "Unknown stdin value";
        }
        if (std::holds_alternative<Range>(value)) {
          LOG(FATAL) << "Range value cannot be read from stdin";
        }
        if (std::holds_alternative<std::shared_ptr<Array>>(value)) {
          LOG(FATAL) << "Array value cannot be read from stdin";
        }
      }
      constexpr auto res = 1;
      call->value = res;
      return {res};
    }
    if (call->name == "stdout") {
      for (const auto &exp : call->expressions) {
        if (const auto value = eval_value(exp);
            std::holds_alternative<std::nullptr_t>(value)) {
          LOG(FATAL) << "Unknown stdout value";
        }
      }
      constexpr auto res = 1;
      call->value = res;
      return {res};
    }
    LOG(FATAL) << "Unknown call statement";
    return nullptr;
  }

  LOG(FATAL) << "Unknown expression type";
  return std::variant<std::nullptr_t, int, bool, char, float, Range,
                      std::shared_ptr<Array>>{};
}

bool SymbolTable::check_array_type(
    const std::shared_ptr<TypeNode> &type,
    const std::shared_ptr<TypeNode> &other) const {
  if (const auto array_type = std::dynamic_pointer_cast<ArrayTypeNode>(type)) {
    if (const auto other_array_type =
            std::dynamic_pointer_cast<ArrayTypeNode>(other)) {
      if (!check_expression(array_type->size)) {
        LOG(FATAL) << "Array size is not a constant";
        return false;
      }
      const auto array_count = eval_value(array_type->size);
      if (const auto other_array_count = eval_value(other_array_type->size);
          check_array_type(array_type->type, other_array_type->type) &&
          std::holds_alternative<int>(array_count) &&
          std::holds_alternative<int>(other_array_count) &&
          std::get<int>(array_count) == std::get<int>(other_array_count)) {
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
    }
  }
  return false;
}

bool SymbolTable::check_expression(const std::shared_ptr<ExpressionNode> &exp) {
  if (exp == nullptr) {
    return false;
  }
  if (const auto constant =
          std::dynamic_pointer_cast<ConstantExpressionNode>(exp)) {
    return true;
  }
  if (const auto binary =
          std::dynamic_pointer_cast<BinaryExpressionNode>(exp)) {
    return check_expression(binary->left) && check_expression(binary->right);
  }
  if (const auto unary = std::dynamic_pointer_cast<UnaryExpressionNode>(exp)) {
    return check_expression(unary->expression);
  }
  if (const auto cast = std::dynamic_pointer_cast<CastExpressionNode>(exp)) {
    return check_expression(cast->expression);
  }
  return false;
}

}  // namespace carlos
