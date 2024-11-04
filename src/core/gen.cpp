//
// Created by 陈洋 on 24-11-4.
//

#include "gen.h"

namespace carlos {
void IRGen::gen_node(const std::shared_ptr<ASTNode> &node) {
  if (const auto program = std::dynamic_pointer_cast<ProgramNode>(node)) {
    gen_program(program);
  } else {
    LOG(FATAL) << "Unknown node type";
  }
}

void IRGen::gen_program(const std::shared_ptr<ProgramNode> &node) {
  std::cout << "@.str.in.int = private unnamed_addr constant [3 x i8] "
               "c\"%d\\00\", align 1\n";
  std::cout << "@.str.in.float = private unnamed_addr constant [3 x i8] "
               "c\"%f\\00\", align 1\n";
  std::cout << "@.str.in.char = private unnamed_addr constant [3 x i8] "
               "c\"%c\\00\", align 1\n";
  std::cout << "@.str.in.bool = private unnamed_addr constant [3 x i8] "
               "c\"%d\\00\", align 1\n";

  std::cout << "@.str.out.int = private unnamed_addr constant [3 x i8] "
               "c\"%d\\00\", align 1\n";
  std::cout << "@.str.out.float = private unnamed_addr constant [3 x i8] "
               "c\"%f\\00\", align 1\n";
  std::cout << "@.str.out.char = private unnamed_addr constant [3 x i8] "
               "c\"%c\\00\", align 1\n";
  std::cout << "@.str.out.bool = private unnamed_addr constant [3 x i8] "
               "c\"%d\\00\", align 1\n";

  std::cout << "declare i32 @scanf(i8*, ...)\n";
  std::cout << "declare i32 @printf(i8*, ...)\n";

  gen_entry(node->entry);
}

void IRGen::gen_entry(const std::shared_ptr<EntryNode> &node) {
  std::cout << "define i32 @main() {\n";
  std::cout << "entry:\n";
  gen_statement(node->statements);
  std::cout << "ret i32 0\n";
  std::cout << "}\n";
}

void IRGen::gen_statement(const std::shared_ptr<StatementNode> &node) {
  if (node == nullptr) {
    return;
  }
  if (const auto statements = std::dynamic_pointer_cast<StatementsNode>(node)) {
    enter_scope();
    for (const auto &statement : statements->statements) {
      gen_statement(statement);
    }
    exit_scope();
  } else if (const auto declaration =
                 std::dynamic_pointer_cast<DeclarationStatementNode>(node)) {
    gen_declaration(declaration);
  } else if (const auto expression =
                 std::dynamic_pointer_cast<ExpressionStatementNode>(node)) {
    gen_expression(expression->expression);
  } else if (const auto call =
                 std::dynamic_pointer_cast<CallStatementNode>(node)) {
    gen_call(call);
  } else if (const auto if_stat =
                 std::dynamic_pointer_cast<IfStatementNode>(node)) {
    gen_if(if_stat);
  } else if (const auto while_stat =
                 std::dynamic_pointer_cast<WhileStatementNode>(node)) {
    gen_while(while_stat);
  } else if (const auto for_stat =
                 std::dynamic_pointer_cast<ForStatementNode>(node)) {
    gen_for(for_stat);
  } else {
    LOG(FATAL) << "Unknown statement type";
  }
}

void IRGen::gen_declaration(
    const std::shared_ptr<DeclarationStatementNode> &node) {
  const auto label = get_label(node->identifier->name);
  const auto alias = node->identifier->name + std::to_string(label);
  add_symbol(node->identifier->name, alias, node->identifier->value);
  if (const auto value = &node->identifier->value;
      std::holds_alternative<int>(*value)) {
    const auto exp_label = gen_expression(node->expression);
    std::cout << "%" << alias << " = alloca i32\n";
    std::cout << "store i32 %" << exp_label << ", i32* %" << alias << "\n";
  } else if (std::holds_alternative<float>(*value)) {
    const auto exp_label = gen_expression(node->expression);
    std::cout << "%" << alias << " = alloca float\n";
    std::cout << "store float %" << exp_label << ", float* %" << alias << "\n";
  } else if (std::holds_alternative<char>(*value)) {
    const auto exp_label = gen_expression(node->expression);
    std::cout << "%" << alias << " = alloca i8\n";
    std::cout << "store i8 %" << exp_label << ", i8* %" << alias << "\n";
  } else if (std::holds_alternative<bool>(*value)) {
    const auto exp_label = gen_expression(node->expression);
    std::cout << "%" << alias << " = alloca i1\n";
    std::cout << "store i1 %" << exp_label << ", i1* %" << alias << "\n";
  } else {
    // TODO: Array
    LOG(FATAL) << "Unknown type";
  }
}

void IRGen::gen_call(const std::shared_ptr<CallStatementNode> &node) {
  if (node->name == "stdin") {
    for (const auto &args : node->expressions) {
      if (const auto id =
              std::dynamic_pointer_cast<IdentifierExpressionNode>(args)) {
        const auto symbol = get_symbol(id->name);
        const auto value = &symbol->value;
        const auto label = next_label();
        if (std::holds_alternative<int>(*value)) {
          std::cout
              << "%" << label
              << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds "
                 "([3 x i8], [3 x i8]* @.str.in.int, i32 0), i32* %"
              << symbol->alias << ")\n";
        } else if (std::holds_alternative<float>(*value)) {
          std::cout
              << "%" << label
              << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds "
                 "([3 x i8], [3 x i8]* @.str.in.float, i32 0), float* %"
              << symbol->alias << ")\n";
        } else if (std::holds_alternative<char>(*value)) {
          std::cout
              << "%" << label
              << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds "
                 "([3 x i8], [3 x i8]* @.str.in.char, i32 0), i8* %"
              << symbol->alias << ")\n";
        } else if (std::holds_alternative<bool>(*value)) {
          std::cout
              << "%" << label
              << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds "
                 "([3 x i8], [3 x i8]* @.str.in.bool, i32 0), i1* %"
              << symbol->alias << ")\n";
        } else {
          LOG(FATAL) << "Unknown type";
        }

      } else if (const auto ac =
                     std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                         args)) {
        // TODO: Array
      } else {
        LOG(FATAL) << "Unknown expression";
      }
    }
  } else if (node->name == "stdout") {
    auto labels = std::vector<std::tuple<std::string, int>>{};
    for (const auto &arg : node->expressions) {
      const auto label = gen_expression(arg);
      const auto value = &arg->value;
      if (std::holds_alternative<int>(*value)) {
        labels.emplace_back("i32", label);
      } else if (std::holds_alternative<float>(*value)) {
        labels.emplace_back("f32", label);
      } else if (std::holds_alternative<char>(*value)) {
        labels.emplace_back("char", label);
      } else if (std::holds_alternative<bool>(*value)) {
        labels.emplace_back("bool", label);
      } else {
        LOG(FATAL) << "Unknown type";
      }
    }
    for (const auto &[type, label] : labels) {
      if (type == "i32") {
        const auto return_label = next_label();
        std::cout
            << "%" << return_label
            << " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds "
               "([3 x i8], [3 x i8]* @.str.out.int, i32 0), i32 %"
            << label << ")\n";
      } else if (type == "f32") {
        const auto casted_label = next_label();
        const auto return_label = next_label();
        std::cout << "%" << casted_label << " = fpext float %" << label
                  << " to double\n";
        std::cout
            << "%" << return_label
            << " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds "
               "([3 x i8], [3 x i8]* @.str.out.float, i32 0), double %"
            << casted_label << ")\n";
      } else if (type == "char") {
        const auto return_label = next_label();
        std::cout
            << "%" << return_label
            << " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds "
               "([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %"
            << label << ")\n";
      } else if (type == "bool") {
        const auto return_label = next_label();
        std::cout
            << "%" << return_label
            << " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds "
               "([3 x i8], [3 x i8]* @.str.out.bool, i32 0), i1 %"
            << label << ")\n";
      } else {
        LOG(FATAL) << "Unknown type";
      }
    }

  } else {
    LOG(FATAL) << "Unknown function";
  }
}

void IRGen::gen_while(const std::shared_ptr<WhileStatementNode> &node) {
  const auto while_label = next_while_label();
  std::cout << "br label %while" << while_label << ".cond\n";
  std::cout << "while" << while_label << ".cond:\n";
  const auto cond_label = gen_expression(node->condition);
  std::cout << "br i1 %" << cond_label << ", label %while" << while_label
            << ".body, label %while" << while_label << ".end\n";
  std::cout << "while" << while_label << ".body:\n";
  gen_statement(node->body);
  std::cout << "br label %while" << while_label << ".cond\n";
  std::cout << "while" << while_label << ".end:\n";
}

void IRGen::gen_if(const std::shared_ptr<IfStatementNode> &node) {
  if (node->condition) {
    const auto if_label = next_if_label();
    const auto condition_label = gen_expression(node->condition);
    if (begin_if == 0) {
      begin_if = if_label;
    }
    if (node->else_body) {
      std::cout << "br i1 %" << condition_label << ", label %if" << if_label
                << ".then, label %if" << if_label << ".else\n";
      std::cout << "if" << if_label << ".then:\n";
      gen_statement(node->then_body);
      std::cout << "br label %if" << begin_if << ".end\n";
      std::cout << "if" << if_label << ".else:\n";
      gen_statement(node->else_body);
    } else {
      std::cout << "br i1 %" << condition_label << ", label %if" << if_label
                << ".then, label %if" << begin_if << ".end\n";
      std::cout << "if" << if_label << ".then:\n";
      gen_statement(node->then_body);
      std::cout << "br label %if" << begin_if << ".end\n";
      std::cout << "if" << begin_if << ".end:\n";
      begin_if = 0;
    }
  } else {
    gen_statement(node->then_body);
    std::cout << "br label %if" << begin_if << ".end\n";
    std::cout << "if" << begin_if << ".end:\n";
    begin_if = 0;
  }
}

void IRGen::gen_for(const std::shared_ptr<ForStatementNode> &node) {
  const auto for_label = next_for_label();
  const auto iter_label = get_label(node->iter->name);
  const auto alias = node->iter->name + std::to_string(iter_label);
  add_symbol_to_next_scope(node->iter->name, alias, node->iter->value);
  const auto range_label = gen_expression(node->iterator);
  CHECK_EQ(range_label, 0);
  const auto start_label = std::get<0>(range_labels);
  const auto end_label = std::get<1>(range_labels);
  const auto inclusive = std::get<2>(range_labels);
  const auto alias_label = next_label();
  const auto cmp_label = next_label();
  std::cout << "%" << alias << " = alloca i32\n";
  std::cout << "store i32 %" << start_label << ", i32* %" << alias << "\n";
  std::cout << "br label %for" << for_label << ".cond\n";
  std::cout << "for" << for_label << ".cond:\n";
  if (inclusive) {
    std::cout << "%" << alias_label << " = load i32, i32* %" << alias << "\n";
    std::cout << "%" << cmp_label << " = icmp sle i32 %" << alias_label << ", %"
              << end_label << "\n";
  } else {
    std::cout << "%" << alias_label << " = load i32, i32* %" << alias << "\n";
    std::cout << "%" << cmp_label << " = icmp slt i32 %" << alias_label << ", %"
              << end_label << "\n";
  }
  std::cout << "br i1 %" << cmp_label << ", label %for" << for_label
            << ".body, label %for" << for_label << ".end\n";
  std::cout << "for" << for_label << ".body:\n";
  gen_statement(node->body);
  const auto temp_alias = next_label();
  const auto add_label = next_label();
  std::cout << "%" << temp_alias << " = load i32, i32* %" << alias << "\n";
  std::cout << "%" << add_label << " = add i32 %" << temp_alias << ", 1\n";
  std::cout << "store i32 %" << add_label << ", i32* %" << alias << "\n";
  std::cout << "br label %for" << for_label << ".cond\n";
  std::cout << "for" << for_label << ".end:\n";
  range_labels = {0, 0, false};
}

int IRGen::gen_expression(const std::shared_ptr<ExpressionNode> &node) {
  if (const auto binary =
          std::dynamic_pointer_cast<BinaryExpressionNode>(node)) {
    if (binary->is_constant) {
      return gen_expression(
          std::make_shared<ConstantExpressionNode>(binary->value));
    }
    const auto left_label = gen_expression(binary->left);
    const auto right_label = gen_expression(binary->right);
    const auto op = binary->op;
    const auto left_value = &binary->left->value;
    const auto right_value = &binary->right->value;
    if (std::holds_alternative<int>(*left_value) &&
        std::holds_alternative<int>(*right_value)) {
      if (op == "+") {
        const auto label = next_label();
        std::cout << "%" << label << " = add i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "-") {
        const auto label = next_label();
        std::cout << "%" << label << " = sub i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "*") {
        const auto label = next_label();
        std::cout << "%" << label << " = mul i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "/") {
        const auto label = next_label();
        std::cout << "%" << label << " = sdiv i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "%") {
        const auto label = next_label();
        std::cout << "%" << label << " = srem i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "==") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp eq i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "!=") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp ne i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "<") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp slt i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "<=") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sle i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == ">") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sgt i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == ">=") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sge i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          std::cout << "store i32 %" << right_label << ", i32* %"
                    << symbol->alias << "\n";

          return 0;
        }
      }
      if (op == "+=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          const auto label = next_label();
          std::cout << "%" << label << " = add i32 %" << left_label << ", %"
                    << right_label << "\n";
          std::cout << "store i32 %" << label << ", i32* %" << symbol->alias
                    << "\n";

          return 0;
        }
      }
      if (op == "-=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          const auto label = next_label();
          std::cout << "%" << label << " = sub i32 %" << left_label << ", %"
                    << right_label << "\n";
          std::cout << "store i32 %" << label << ", i32* %" << symbol->alias
                    << "\n";

          return 0;
        }
      }
      if (op == "*=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          const auto label = next_label();
          std::cout << "%" << label << " = mul i32 %" << left_label << ", %"
                    << right_label << "\n";
          std::cout << "store i32 %" << label << ", i32* %" << symbol->alias
                    << "\n";

          return 0;
        }
      }
      if (op == "/=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          const auto label = next_label();
          std::cout << "%" << label << " = sdiv i32 %" << left_label << ", %"
                    << right_label << "\n";
          std::cout << "store i32 %" << label << ", i32* %" << symbol->alias
                    << "\n";

          return 0;
        }
      }
      if (op == "%=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          const auto label = next_label();
          std::cout << "%" << label << " = srem i32 %" << left_label << ", %"
                    << right_label << "\n";
          std::cout << "store i32 %" << label << ", i32* %" << symbol->alias
                    << "\n";

          return 0;
        }
      }
      if (op == "..") {
        range_labels = {left_label, right_label, false};
        return 0;
      }
      if (op == "..=") {
        range_labels = {left_label, right_label, true};
        return 0;
      }

      LOG(FATAL) << "Unknown operator";
      return -1;
    }
    if (std::holds_alternative<float>(*left_value) &&
        std::holds_alternative<float>(*right_value)) {
      if (op == "+") {
        const auto label = next_label();
        std::cout << "%" << label << " = fadd float %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "-") {
        const auto label = next_label();
        std::cout << "%" << label << " = fsub float %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "*") {
        const auto label = next_label();
        std::cout << "%" << label << " = fmul float %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "/") {
        const auto label = next_label();
        std::cout << "%" << label << " = fdiv float %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "==") {
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp oeq float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == "!=") {
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp one float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == "<") {
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp olt float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == "<=") {
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp ole float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == ">") {
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp ogt float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == ">=") {
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp oge float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == "=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          std::cout << "store float %" << right_label << ", float* %"
                    << symbol->alias << "\n";

          return 0;
        }
      }
      if (op == "+=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          const auto label = next_label();
          std::cout << "%" << label << " = fadd float %" << left_label << ", %"
                    << right_label << "\n";
          std::cout << "store float %" << label << ", float* %" << symbol->alias
                    << "\n";

          return 0;
        }
      }
      if (op == "-=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          const auto label = next_label();
          std::cout << "%" << label << " = fsub float %" << left_label << ", %"
                    << right_label << "\n";
          std::cout << "store float %" << label << ", float* %" << symbol->alias
                    << "\n";

          return 0;
        }
      }
      if (op == "*=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          const auto label = next_label();
          std::cout << "%" << label << " = fmul float %" << left_label << ", %"
                    << right_label << "\n";
          std::cout << "store float %" << label << ", float* %" << symbol->alias
                    << "\n";

          return 0;
        }
      }
      if (op == "/=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          const auto label = next_label();
          std::cout << "%" << label << " = fdiv float %" << left_label << ", %"
                    << right_label << "\n";
          std::cout << "store float %" << label << ", float* %" << symbol->alias
                    << "\n";

          return 0;
        }
      }

      LOG(FATAL) << "Unknown operator";
      return -1;
    }
    if (std::holds_alternative<char>(*left_value) &&
        std::holds_alternative<char>(*right_value)) {
      if (op == "==") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp eq i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "!=") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp ne i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "<") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp slt i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "<=") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sle i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == ">") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sgt i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == ">=") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sge i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          std::cout << "store i8 %" << right_label << ", i8* %" << symbol->alias
                    << "\n";

          return 0;
        }
      }

      LOG(FATAL) << "Unknown operator";
      return -1;
    }
    if (std::holds_alternative<bool>(*left_value) &&
        std::holds_alternative<bool>(*right_value)) {
      if (op == "==") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp eq i1 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "!=") {
        const auto label = next_label();
        std::cout << "%" << label << " = icmp ne i1 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "&&") {
        const auto label = next_label();
        std::cout << "%" << label << " = and i1 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "||") {
        const auto label = next_label();
        std::cout << "%" << label << " = or i1 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "=") {
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          std::cout << "store i1 %" << right_label << ", i1* %" << symbol->alias
                    << "\n";

          return 0;
        }
      }

      LOG(FATAL) << "Unknown operator";
      return -1;
    }
    LOG(FATAL) << "Unknown type";
    return -1;
  }
  if (const auto unary = std::dynamic_pointer_cast<UnaryExpressionNode>(node)) {
    if (unary->is_constant) {
      return gen_expression(
          std::make_shared<ConstantExpressionNode>(unary->value));
    }
    const auto label = gen_expression(unary->expression);
    const auto op = unary->op;
    const auto value = &unary->expression->value;
    if (std::holds_alternative<int>(*value)) {
      if (op == "+") {
        return label;
      }
      if (op == "-") {
        const auto new_label = next_label();
        std::cout << "%" << new_label << " = sub i32 0, %" << label << "\n";
        return new_label;
      }
      LOG(FATAL) << "Unknown operator";
      return -1;
    }

    if (std::holds_alternative<float>(*value)) {
      if (op == "+") {
        return label;
      }
      if (op == "-") {
        const auto new_label = next_label();
        std::cout << "%" << new_label << " = fsub float 0.0, %" << label
                  << "\n";
        return new_label;
      }
      LOG(FATAL) << "Unknown operator";
      return -1;
    }

    if (std::holds_alternative<bool>(*value)) {
      if (op == "!") {
        const auto new_label = next_label();
        std::cout << "%" << new_label << " = xor i1 %" << label << ", true\n";
        return new_label;
      }
      LOG(FATAL) << "Unknown operator";
      return -1;
    }

    LOG(FATAL) << "Unknown type";
    return -1;
  }
  if (const auto constant =
          std::dynamic_pointer_cast<ConstantExpressionNode>(node)) {
    const auto value = &constant->value;
    if (std::holds_alternative<int>(*value)) {
      const auto label = next_label();
      std::cout << "%" << label << " = add i32 0, " << std::get<int>(*value)
                << "\n";
      return label;
    }
    if (std::holds_alternative<float>(*value)) {
      const auto label = next_label();
      std::cout << "%" << label << " = fadd float 0.0, " << std::showpoint
                << std::get<float>(*value) << "\n";
      return label;
    }
    if (std::holds_alternative<char>(*value)) {
      const auto label = next_label();
      std::cout << "%" << label << " = add i8 0, "
                << static_cast<int>(std::get<char>(*value)) << "\n";
      return label;
    }
    if (std::holds_alternative<bool>(*value)) {
      const auto label = next_label();
      std::cout << "%" << label << " = add i1 0, "
                << static_cast<int>(std::get<bool>(*value)) << "\n";
      return label;
    }
    LOG(FATAL) << "Unknown constant type";
    return -1;
  }
  if (const auto identifier =
          std::dynamic_pointer_cast<IdentifierExpressionNode>(node)) {
    const auto symbol = get_symbol(identifier->name);
    if (symbol == nullptr) {
      LOG(FATAL) << "Unknown identifier";
    }
    const auto value = &symbol->value;
    if (std::holds_alternative<int>(*value)) {
      const auto label = next_label();
      std::cout << "%" << label << " = load i32, i32* %" << symbol->alias
                << "\n";
      return label;
    }
    if (std::holds_alternative<float>(*value)) {
      const auto label = next_label();
      std::cout << "%" << label << " = load float, float* %" << symbol->alias
                << "\n";
      return label;
    }
    if (std::holds_alternative<char>(*value)) {
      const auto label = next_label();
      std::cout << "%" << label << " = load i8, i8* %" << symbol->alias << "\n";
      return label;
    }
    if (std::holds_alternative<bool>(*value)) {
      const auto label = next_label();
      std::cout << "%" << label << " = load i1, i1* %" << symbol->alias << "\n";
      return label;
    }
    LOG(FATAL) << "Unknown identifier type";
    return -1;
  }
  LOG(FATAL) << "Unknown expression type";
  return -1;
}

}  // namespace carlos
