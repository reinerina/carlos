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
    if (on_break) {
      return;
    }
    gen_declaration(declaration);
  } else if (const auto expression =
                 std::dynamic_pointer_cast<ExpressionStatementNode>(node)) {
    if (on_break) {
      return;
    }
    gen_expression(expression->expression);
  } else if (const auto if_stat =
                 std::dynamic_pointer_cast<IfStatementNode>(node)) {
    if (on_break && begin_if == 0) {
      return;
    }
    gen_if(if_stat);
  } else if (const auto while_stat =
                 std::dynamic_pointer_cast<WhileStatementNode>(node)) {
    if (on_break) {
      return;
    }
    if (control_stage_index == 0) {
      control_stage.clear();
    }
    control_stage.push_back(1);
    control_stage_index += 1;
    gen_while(while_stat);
    control_stage_index -= 1;
  } else if (const auto for_stat =
                 std::dynamic_pointer_cast<ForStatementNode>(node)) {
    if (on_break) {
      return;
    }
    if (control_stage_index == 0) {
      control_stage.clear();
    }
    control_stage.push_back(2);
    control_stage_index += 1;
    gen_for(for_stat);
    control_stage_index -= 1;
  } else if (const auto control =
                 std::dynamic_pointer_cast<ControlStatementNode>(node)) {
    if (on_break) {
      return;
    }
    gen_control(control);
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
  } else if (std::holds_alternative<std::shared_ptr<Array>>(*value)) {
    const auto exp_label = gen_expression(node->expression);
    const auto array_value = std::get<std::shared_ptr<Array>>(*value);
    const auto basic_type = array_value->basic_value();
    const auto dims = std::get<std::shared_ptr<Array>>(*value)->dimensions();
    auto count = 1;
    for (const auto &dim : dims) {
      count *= dim;
    }
    const auto temp_label = next_label();
    if (std::holds_alternative<int>(basic_type)) {
      std::cout << "%" << temp_label << " = alloca ["
                << std::to_string(count) + " x i32]*\n";
      std::cout << "store [" << std::to_string(count) + " x i32]* %"
                << exp_label << ", [" << std::to_string(count) + " x i32]** %"
                << temp_label << "\n";
      std::cout << "%" << alias << "= load [" << std::to_string(count)
                << " x i32]*, [" << std::to_string(count) << " x i32]** %"
                << temp_label << "\n";
    } else if (std::holds_alternative<float>(basic_type)) {
      std::cout << "%" << temp_label << " = alloca ["
                << std::to_string(count) + " x float]*\n";
      std::cout << "store [" << std::to_string(count) + " x float]* %"
                << exp_label << ", [" << std::to_string(count) + " x float]** %"
                << temp_label << "\n";
      std::cout << "%" << alias << "= load [" << std::to_string(count)
                << " x float]*, [" << std::to_string(count) << " x float]** %"
                << temp_label << "\n";
    } else if (std::holds_alternative<char>(basic_type)) {
      std::cout << "%" << temp_label << " = alloca ["
                << std::to_string(count) + " x i8]*\n";
      std::cout << "store [" << std::to_string(count) + " x i8]* %" << exp_label
                << ", [" << std::to_string(count) + " x i8]** %" << temp_label
                << "\n";
      std::cout << "%" << alias << "= load [" << std::to_string(count)
                << " x i8]*, [" << std::to_string(count) << " x i8]** %"
                << temp_label << "\n";
    } else if (std::holds_alternative<bool>(basic_type)) {
      std::cout << "%" << temp_label << " = alloca ["
                << std::to_string(count) + " x i1]*\n";
      std::cout << "store [" << std::to_string(count) + " x i1]* %" << exp_label
                << ", [" << std::to_string(count) + " x i1]** %" << temp_label
                << "\n";
      std::cout << "%" << alias << "= load [" << std::to_string(count)
                << " x i1]*, [" << std::to_string(count) << " x i1]** %"
                << temp_label << "\n";
    } else {
      LOG(FATAL) << "Unknown type";
    }
  } else {
    LOG(FATAL) << "Unknown type";
  }
}
void IRGen::gen_while(const std::shared_ptr<WhileStatementNode> &node) {
  const auto while_label = next_while_label();
  if (!on_break) {
    std::cout << "br label %while" << while_label << ".cond\n";
  }
  on_break = false;
  std::cout << "while" << while_label << ".cond:\n";
  if (!on_break) {
    const auto cond_label = gen_expression(node->condition);
    std::cout << "br i1 %" << cond_label << ", label %while" << while_label
              << ".body, label %while" << while_label << ".end\n";
  }
  on_break = false;
  std::cout << "while" << while_label << ".body:\n";
  gen_statement(node->body);
  if (!on_break) {
    std::cout << "br label %while" << while_label << ".cond\n";
  }
  on_break = false;
  std::cout << "while" << while_label << ".end:\n";
}

void IRGen::gen_if(const std::shared_ptr<IfStatementNode> &node) {
  if (node->condition) {
    const auto if_label = next_if_label();
    if (begin_if == 0) {
      begin_if = if_label;
    }
    if (node->else_body) {
      if (!on_break) {
        const auto condition_label = gen_expression(node->condition);
        std::cout << "br i1 %" << condition_label << ", label %if" << if_label
                  << ".then, label %if" << if_label << ".else\n";
      }
      on_break = false;
      std::cout << "if" << if_label << ".then:\n";
      gen_statement(node->then_body);
      if (!on_break) {
        std::cout << "br label %if" << begin_if << ".end\n";
      }
      on_break = false;
      std::cout << "if" << if_label << ".else:\n";
      gen_statement(node->else_body);
    } else {
      if (!on_break) {
        const auto condition_label = gen_expression(node->condition);
        std::cout << "br i1 %" << condition_label << ", label %if" << if_label
                  << ".then, label %if" << begin_if << ".end\n";
      }
      on_break = false;
      std::cout << "if" << if_label << ".then:\n";
      gen_statement(node->then_body);
      if (!on_break) {
        std::cout << "br label %if" << begin_if << ".end\n";
      }
      on_break = false;
      std::cout << "if" << begin_if << ".end:\n";
      begin_if = 0;
    }
  } else {
    gen_statement(node->then_body);
    if (!on_break) {
      std::cout << "br label %if" << begin_if << ".end\n";
    }
    on_break = false;
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
  const auto temp_start_label = next_label();
  const auto end_label = std::get<1>(range_labels);
  const auto inclusive = std::get<2>(range_labels);
  const auto temp_alias = next_label();
  const auto add_label = next_label();
  const auto alias_label = next_label();
  const auto cmp_label = next_label();
  std::cout << "%" << alias << " = alloca i32\n";
  std::cout << "%" << temp_start_label << " = sub i32 %" << start_label
            << ", 1\n";
  std::cout << "store i32 %" << temp_start_label << ", i32* %" << alias << "\n";
  if (!on_break) {
    std::cout << "br label %for" << for_label << ".cond\n";
  }
  on_break = false;
  std::cout << "for" << for_label << ".cond:\n";

  std::cout << "%" << temp_alias << " = load i32, i32* %" << alias << "\n";
  std::cout << "%" << add_label << " = add i32 %" << temp_alias << ", 1\n";
  std::cout << "store i32 %" << add_label << ", i32* %" << alias << "\n";
  if (inclusive) {
    std::cout << "%" << alias_label << " = load i32, i32* %" << alias << "\n";
    std::cout << "%" << cmp_label << " = icmp sle i32 %" << alias_label << ", %"
              << end_label << "\n";
  } else {
    std::cout << "%" << alias_label << " = load i32, i32* %" << alias << "\n";
    std::cout << "%" << cmp_label << " = icmp slt i32 %" << alias_label << ", %"
              << end_label << "\n";
  }
  if (!on_break) {
    std::cout << "br i1 %" << cmp_label << ", label %for" << for_label
              << ".body, label %for" << for_label << ".end\n";
  }
  on_break = false;
  std::cout << "for" << for_label << ".body:\n";
  gen_statement(node->body);
  if (!on_break) {
    std::cout << "br label %for" << for_label << ".cond\n";
  }
  on_break = false;
  std::cout << "for" << for_label << ".end:\n";
  range_labels = {0, 0, false};
}

void IRGen::gen_control(const std::shared_ptr<ControlStatementNode> &node) {
  const auto current_control = control_stage.back();
  if (current_control == 1) {
    if (node->type == "break") {
      std::cout << "br label %while" << current_while_label() << ".end\n";
    } else if (node->type == "continue") {
      std::cout << "br label %while" << current_while_label() << ".cond\n";
    }
    on_break = true;
  } else if (current_control == 2) {
    if (node->type == "break") {
      std::cout << "br label %for" << current_for_label() << ".end\n";
    } else if (node->type == "continue") {
      std::cout << "br label %for" << current_for_label() << ".cond\n";
    }
    on_break = true;
  }
}

int IRGen::gen_expression(const std::shared_ptr<ExpressionNode> &node) {
  if (const auto binary =
          std::dynamic_pointer_cast<BinaryExpressionNode>(node)) {
    if (binary->is_constant) {
      return gen_expression(
          std::make_shared<ConstantExpressionNode>(binary->value));
    }

    const auto op = binary->op;
    const auto left_value = &binary->left->value;
    const auto right_value = &binary->right->value;
    if (std::holds_alternative<int>(*left_value) &&
        std::holds_alternative<int>(*right_value)) {
      if (op == "+") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = add i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "-") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = sub i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "*") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = mul i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "/") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = sdiv i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "%") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = srem i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "==") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp eq i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "!=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp ne i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "<") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp slt i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "<=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sle i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == ">") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sgt i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == ">=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sge i32 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "=") {
        const auto right_label = gen_expression(binary->right);
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          std::cout << "store i32 %" << right_label << ", i32* %"
                    << symbol->alias << "\n";

          return 0;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          array_pointer = true;
          const auto left_label = gen_expression(binary->left);
          std::cout << "store i32 %" << right_label << ", i32* %" << left_label
                    << "\n";
          array_pointer = false;
          return 0;
        }
      }
      if (op == "+=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
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
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          const auto label = next_label();
          std::cout << "%" << label << " = add i32 %" << left_label << ", %"
                    << right_label << "\n";
          array_pointer = true;
          const auto left_alias = gen_expression(binary->left);
          std::cout << "store i32 %" << label << ", i32* %" << left_alias
                    << "\n";
          array_pointer = false;
          return 0;
        }
      }
      if (op == "-=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
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
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          const auto label = next_label();
          std::cout << "%" << label << " = sub i32 %" << left_label << ", %"
                    << right_label << "\n";
          array_pointer = true;
          const auto left_alias = gen_expression(binary->left);
          std::cout << "store i32 %" << label << ", i32* %" << left_alias
                    << "\n";
          array_pointer = false;
          return 0;
        }
      }
      if (op == "*=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
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
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          const auto label = next_label();
          std::cout << "%" << label << " = mul i32 %" << left_label << ", %"
                    << right_label << "\n";
          array_pointer = true;
          const auto left_alias = gen_expression(binary->left);
          std::cout << "store i32 %" << label << ", i32* %" << left_alias
                    << "\n";
          array_pointer = false;
          return 0;
        }
      }
      if (op == "/=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
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
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          const auto label = next_label();
          std::cout << "%" << label << " = sdiv i32 %" << left_label << ", %"
                    << right_label << "\n";
          array_pointer = true;
          const auto left_alias = gen_expression(binary->left);
          std::cout << "store i32 %" << label << ", i32* %" << left_alias
                    << "\n";
          array_pointer = false;
          return 0;
        }
      }
      if (op == "%=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
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
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          const auto label = next_label();
          std::cout << "%" << label << " = srem i32 %" << left_label << ", %"
                    << right_label << "\n";
          array_pointer = true;
          const auto left_alias = gen_expression(binary->left);
          std::cout << "store i32 %" << label << ", i32* %" << left_alias
                    << "\n";
          array_pointer = false;
          return 0;
        }
      }
      if (op == "..") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        range_labels = {left_label, right_label, false};
        return 0;
      }
      if (op == "..=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        range_labels = {left_label, right_label, true};
        return 0;
      }

      LOG(FATAL) << "Unknown operator";
      return -1;
    }
    if (std::holds_alternative<float>(*left_value) &&
        std::holds_alternative<float>(*right_value)) {
      if (op == "+") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = fadd float %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "-") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = fsub float %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "*") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = fmul float %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "/") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = fdiv float %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "==") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp oeq float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == "!=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp one float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == "<") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp olt float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == "<=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp ole float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == ">") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp ogt float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == ">=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = fcmp oge float %" << left_label
                  << ", %" << right_label << "\n";
        return label;
      }
      if (op == "=") {
        const auto right_label = gen_expression(binary->right);
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          std::cout << "store float %" << right_label << ", float* %"
                    << symbol->alias << "\n";

          return 0;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          array_pointer = true;
          const auto left_label = gen_expression(binary->left);
          std::cout << "store float %" << right_label << ", float* %"
                    << left_label << "\n";
          array_pointer = false;
          return 0;
        }
      }
      if (op == "+=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
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
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          const auto label = next_label();
          std::cout << "%" << label << " = fadd float %" << left_label << ", %"
                    << right_label << "\n";
          array_pointer = true;
          const auto left_alias = gen_expression(binary->left);
          std::cout << "store float %" << label << ", float* %" << left_alias
                    << "\n";
          array_pointer = false;
          return 0;
        }
      }
      if (op == "-=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
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
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          const auto label = next_label();
          std::cout << "%" << label << " = fsub float %" << left_label << ", %"
                    << right_label << "\n";
          array_pointer = true;
          const auto left_alias = gen_expression(binary->left);
          std::cout << "store float %" << label << ", float* %" << left_alias
                    << "\n";
          array_pointer = false;
          return 0;
        }
      }
      if (op == "*=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
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
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          const auto label = next_label();
          std::cout << "%" << label << " = fmul float %" << left_label << ", %"
                    << right_label << "\n";
          array_pointer = true;
          const auto left_alias = gen_expression(binary->left);
          std::cout << "store float %" << label << ", float* %" << left_alias
                    << "\n";
          array_pointer = false;
          return 0;
        }
      }
      if (op == "/=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
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
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          const auto label = next_label();
          std::cout << "%" << label << " = fdiv float %" << left_label << ", %"
                    << right_label << "\n";
          array_pointer = true;
          const auto left_alias = gen_expression(binary->left);
          std::cout << "store float %" << label << ", float* %" << left_alias
                    << "\n";
          array_pointer = false;
          return 0;
        }
      }

      LOG(FATAL) << "Unknown operator";
      return -1;
    }
    if (std::holds_alternative<char>(*left_value) &&
        std::holds_alternative<char>(*right_value)) {
      if (op == "==") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp eq i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "!=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp ne i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "<") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp slt i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "<=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sle i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == ">") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sgt i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == ">=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp sge i8 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "=") {
        const auto right_label = gen_expression(binary->right);
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          std::cout << "store i8 %" << right_label << ", i8* %" << symbol->alias
                    << "\n";

          return 0;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          array_pointer = true;
          const auto left_label = gen_expression(binary->left);
          std::cout << "store i8 %" << right_label << ", i8* %" << left_label
                    << "\n";
          array_pointer = false;
          return 0;
        }
      }

      LOG(FATAL) << "Unknown operator";
      return -1;
    }
    if (std::holds_alternative<bool>(*left_value) &&
        std::holds_alternative<bool>(*right_value)) {
      if (op == "==") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp eq i1 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "!=") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = icmp ne i1 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "&&") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = and i1 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "||") {
        const auto left_label = gen_expression(binary->left);
        const auto right_label = gen_expression(binary->right);
        const auto label = next_label();
        std::cout << "%" << label << " = or i1 %" << left_label << ", %"
                  << right_label << "\n";
        return label;
      }
      if (op == "=") {
        const auto right_label = gen_expression(binary->right);
        if (const auto identifier =
                std::dynamic_pointer_cast<IdentifierExpressionNode>(
                    binary->left)) {
          const auto symbol = get_symbol(identifier->name);
          std::cout << "store i1 %" << right_label << ", i1* %" << symbol->alias
                    << "\n";

          return 0;
        }
        if (const auto array_access =
                std::dynamic_pointer_cast<ArrayAccessExpressionNode>(
                    binary->left)) {
          array_pointer = true;
          const auto left_label = gen_expression(binary->left);
          std::cout << "store i1 %" << right_label << ", i1* %" << left_label
                    << "\n";
          array_pointer = false;
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
  if (const auto call = std::dynamic_pointer_cast<CallExpressionNode>(node)) {
    if (call->name == "stdin") {
      for (const auto &args : call->expressions) {
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
          array_pointer = true;
          const auto label = gen_expression(ac);
          const auto return_label = next_label();
          const auto symbol = get_symbol(ac->array->name);
          const auto value = std::get<std::shared_ptr<Array>>(symbol->value);
          const auto basic_type = value->basic_value();
          if (std::holds_alternative<int>(basic_type)) {
            std::cout
                << "%" << return_label
                << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds "
                   "([3 x i8], [3 x i8]* @.str.in.int, i32 0), i32* %"
                << label << ")\n";
          } else if (std::holds_alternative<float>(basic_type)) {
            std::cout
                << "%" << return_label
                << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds "
                   "([3 x i8], [3 x i8]* @.str.in.float, i32 0), float* %"
                << label << ")\n";
          } else if (std::holds_alternative<char>(basic_type)) {
            std::cout
                << "%" << return_label
                << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds "
                   "([3 x i8], [3 x i8]* @.str.in.char, i32 0), i8* %"
                << label << ")\n";
          } else if (std::holds_alternative<bool>(basic_type)) {
            std::cout
                << "%" << return_label
                << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds "
                   "([3 x i8], [3 x i8]* @.str.in.bool, i32 0), i1* %"
                << label << ")\n";
          } else {
            LOG(FATAL) << "Unknown type";
          }
          array_pointer = false;
        } else {
          LOG(FATAL) << "Unknown expression";
          return -1;
        }
      }
      return 0;
    }
    if (call->name == "stdout") {
      auto labels = std::vector<std::tuple<std::string, int>>{};
      for (const auto &arg : call->expressions) {
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
          return -1;
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
      return -1;
    }
    return 0;
  }
  if (const auto cast = std::dynamic_pointer_cast<CastExpressionNode>(node)) {
    const auto label = gen_expression(cast->expression);
    const auto value = &cast->expression->value;
    const auto cast_type = std::dynamic_pointer_cast<BasicTypeNode>(cast->type);
    if (std::holds_alternative<int>(*value)) {
      if (cast_type->type == "i32") {
        return label;
      }
      if (cast_type->type == "f32") {
        const auto cast_label = next_label();
        std::cout << "%" << cast_label << " = sitofp i32 %" << label
                  << " to float\n";
        return cast_label;
      }
      if (cast_type->type == "char") {
        const auto cast_label = next_label();
        std::cout << "%" << cast_label << " = trunc i32 %" << label
                  << " to i8\n";
        return cast_label;
      }
      if (cast_type->type == "bool") {
        const auto cast_label = next_label();
        std::cout << "%" << cast_label << " = icmp ne i32 %" << label
                  << ", 0\n";
      }
    }
    if (std::holds_alternative<float>(*value)) {
      if (cast_type->type == "i32") {
        const auto cast_label = next_label();
        std::cout << "%" << cast_label << " = fptosi float %" << label
                  << " to i32\n";
        return cast_label;
      }
      if (cast_type->type == "f32") {
        return label;
      }
      if (cast_type->type == "char") {
        const auto temp_label = next_label();
        const auto cast_label = next_label();
        std::cout << "%" << temp_label << " = fptosi float %" << label
                  << " to i32\n";
        std::cout << "%" << cast_label << " = trunc i32 %" << temp_label
                  << " to i8\n";
        return cast_label;
      }
      if (cast_type->type == "bool") {
        const auto cast_label = next_label();
        std::cout << "%" << cast_label << " = fcmp une float %" << label
                  << ", 0.0\n";
        return cast_label;
      }
    }
    if (std::holds_alternative<char>(*value)) {
      if (cast_type->type == "i32") {
        const auto cast_label = next_label();
        std::cout << "%" << cast_label << " = sext i8 %" << label
                  << " to i32\n";
        return cast_label;
      }
      if (cast_type->type == "f32") {
        const auto temp_label = next_label();
        const auto cast_label = next_label();
        std::cout << "%" << temp_label << " = sext i8 %" << label
                  << " to i32\n";
        std::cout << "%" << cast_label << " = sitofp i32 %" << temp_label
                  << " to float\n";
        return cast_label;
      }
      if (cast_type->type == "char") {
        return label;
      }
      if (cast_type->type == "bool") {
        const auto cast_label = next_label();
        std::cout << "%" << cast_label << " = icmp ne i8 %" << label << ", 0\n";
        return cast_label;
      }
    }
    if (std::holds_alternative<bool>(*value)) {
      if (cast_type->type == "i32") {
        const auto cast_label = next_label();
        std::cout << "%" << cast_label << " = zext i1 %" << label
                  << " to i32\n";
        return cast_label;
      }
      if (cast_type->type == "f32") {
        const auto temp_label = next_label();
        const auto cast_label = next_label();
        std::cout << "%" << temp_label << " = zext i1 %" << label
                  << " to i32\n";
        std::cout << "%" << cast_label << " = sitofp i32 %" << temp_label
                  << " to float\n";
        return cast_label;
      }
      if (cast_type->type == "char") {
        const auto cast_label = next_label();
        std::cout << "%" << cast_label << " = zext i1 %" << label << " to i8\n";
        return cast_label;
      }
      if (cast_type->type == "bool") {
        return label;
      }
    }
  }
  if (const auto array = std::dynamic_pointer_cast<ArrayExpressionNode>(node)) {
    auto array_value = std::get<std::shared_ptr<Array>>(array->value);
    auto count = 1;
    auto elements = std::vector<std::shared_ptr<ExpressionNode>>{};
    auto const basic_type = array_value->basic_value();
    for (auto const dims = array_value->dimensions(); const auto &dim : dims) {
      count *= dim;
    }
    array->get_all_elements(elements);
    if (std::holds_alternative<int>(basic_type)) {
      const auto label = next_label();
      std::cout << "%" << label << " = alloca [" << count << " x i32]\n";
      for (auto i = 0; i < count; i++) {
        const auto element_label = gen_expression(elements[i]);
        const auto temp_ptr_label = next_label();
        std::cout << "%" << temp_ptr_label << " = getelementptr inbounds ["
                  << count << " x i32], [" << count << " x i32]* %" << label
                  << ", i32 0, i32 " << i << "\n";
        std::cout << "store i32 %" << element_label << ", i32* %"
                  << temp_ptr_label << "\n";
      }
      return label;
    }
    if (std::holds_alternative<float>(basic_type)) {
      const auto label = next_label();
      std::cout << "%" << label << " = alloca [" << count << " x float]\n";
      for (auto i = 0; i < count; i++) {
        const auto element_label = gen_expression(elements[i]);
        const auto temp_ptr_label = next_label();
        std::cout << "%" << temp_ptr_label << " = getelementptr inbounds ["
                  << count << " x float], [" << count << " x float]* %" << label
                  << ", i32 0, i32 " << i << "\n";
        std::cout << "store float %" << element_label << ", float* %"
                  << temp_ptr_label << "\n";
      }
      return label;
    }
    if (std::holds_alternative<char>(basic_type)) {
      const auto label = next_label();
      std::cout << "%" << label << " = alloca [" << count << " x i8]\n";
      for (auto i = 0; i < count; i++) {
        const auto element_label = gen_expression(elements[i]);
        const auto temp_ptr_label = next_label();
        std::cout << "%" << temp_ptr_label << " = getelementptr inbounds ["
                  << count << " x i8], [" << count << " x i8]* %" << label
                  << ", i32 0, i32 " << i << "\n";
        std::cout << "store i8 %" << element_label << ", i8* %"
                  << temp_ptr_label << "\n";
      }
      return label;
    }
    if (std::holds_alternative<bool>(basic_type)) {
      const auto label = next_label();
      std::cout << "%" << label << " = alloca [" << count << " x i1]\n";
      for (auto i = 0; i < count; i++) {
        const auto element_label = gen_expression(elements[i]);
        const auto temp_ptr_label = next_label();
        std::cout << "%" << temp_ptr_label << " = getelementptr inbounds ["
                  << count << " x i1], [" << count << " x i1]* %" << label
                  << ", i32 0, i32 " << i << "\n";
        std::cout << "store i1 %" << element_label << ", i1* %"
                  << temp_ptr_label << "\n";
      }
      return label;
    }
    return -1;
  }
  if (const auto array_access =
          std::dynamic_pointer_cast<ArrayAccessExpressionNode>(node)) {
    const auto symbol = get_symbol(array_access->array->name);
    const auto array_type = std::get<std::shared_ptr<Array>>(symbol->value);
    const auto basic_type = array_type->basic_value();
    const auto dims = array_type->dimensions();
    const auto indices = &array_access->indices;
    auto index_label = 0;
    auto count = 1;
    for (const auto &dim : dims) {
      count *= dim;
    }
    for (auto i = 0; i < indices->size(); i++) {
      const auto index = gen_expression(indices->at(i));
      if (i == indices->size() - 1) {
        const auto temp_label = next_label();
        std::cout << "%" << temp_label << " = add i32 " << "%" << index_label
                  << ", %" << index << "\n";
        index_label = temp_label;
      } else if (i == 0) {
        const auto dim = dims[i];
        const auto dim_label = next_label();
        std::cout << "%" << dim_label << " = mul i32 %" << index << ", " << dim
                  << "\n";
        const auto temp_label = next_label();
        std::cout << "%" << temp_label << " = add i32 0, %" << dim_label
                  << "\n";
        index_label = temp_label;
      } else {
        const auto dim = dims[i];
        const auto dim_label = next_label();
        std::cout << "%" << dim_label << " = mul i32 %" << index << ", " << dim
                  << "\n";
        const auto temp_label = next_label();
        std::cout << "%" << temp_label << " = add i32 " << "%" << index_label
                  << ", %" << dim_label << "\n";
        index_label = temp_label;
      }
    }
    if (std::holds_alternative<int>(basic_type)) {
      const auto access_label = next_label();
      std::cout << "%" << access_label << " = getelementptr inbounds [" << count
                << " x i32], [" << count << " x i32]* %" << symbol->alias
                << ", i32 0, i32 %" << index_label << "\n";
      if (array_pointer) {
        return access_label;
      }
      const auto temp_label = next_label();
      std::cout << "%" << temp_label << " = load i32, i32* %" << access_label
                << "\n";
      return temp_label;
    }
    if (std::holds_alternative<float>(basic_type)) {
      const auto access_label = next_label();
      std::cout << "%" << access_label << " = getelementptr inbounds [" << count
                << " x float], [" << count << " x float]* %" << symbol->alias
                << ", i32 0, i32 %" << index_label << "\n";
      if (array_pointer) {
        return access_label;
      }
      const auto temp_label = next_label();
      std::cout << "%" << temp_label << " = load float, float* %"
                << access_label << "\n";
      return temp_label;
    }
    if (std::holds_alternative<char>(basic_type)) {
      const auto access_label = next_label();
      std::cout << "%" << access_label << " = getelementptr inbounds [" << count
                << " x i8], [" << count << " x i8]* %" << symbol->alias
                << ", i32 0, i32 %" << index_label << "\n";
      if (array_pointer) {
        return access_label;
      }
      const auto temp_label = next_label();
      std::cout << "%" << temp_label << " = load i8, i8* %" << access_label
                << "\n";
      return temp_label;
    }
    if (std::holds_alternative<bool>(basic_type)) {
      const auto access_label = next_label();
      std::cout << "%" << access_label << " = getelementptr inbounds [" << count
                << " x i1], [" << count << " x i1]* %" << symbol->alias
                << ", i32 0, i32 %" << index_label << "\n";
      if (array_pointer) {
        return access_label;
      }
      const auto temp_label = next_label();
      std::cout << "%" << temp_label << " = load i1, i1* %" << access_label
                << "\n";
      return temp_label;
    }
    return 0;
  }

  LOG(FATAL) << "Unknown expression type";
  return -1;
}

}  // namespace carlos
