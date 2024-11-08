// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

// "%code top" blocks.
#line 31 "carlos.ypp"

  #include "carlos.lex.h"

#line 43 "carlos.parser.cpp"




#include "carlos.parser.h"


// Unqualified %code blocks.
#line 35 "carlos.ypp"

  #define yylex lexer.lex

#line 56 "carlos.parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 17 "carlos.ypp"
namespace carlos {
#line 149 "carlos.parser.cpp"

  /// Build a parser object.
  CarlosParser::CarlosParser (CarlosLexer &lexer_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg)
  {}

  CarlosParser::~CarlosParser ()
  {}

  CarlosParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  CarlosParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  CarlosParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  CarlosParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  CarlosParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  CarlosParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  CarlosParser::symbol_kind_type
  CarlosParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  CarlosParser::stack_symbol_type::stack_symbol_type ()
  {}

  CarlosParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_CA_CHAR_CONST: // CA_CHAR_CONST
        value.YY_MOVE_OR_COPY< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CA_FLOAT_CONST: // CA_FLOAT_CONST
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CA_INT_CONST: // CA_INT_CONST
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_access: // array_access
        value.YY_MOVE_OR_COPY< std::shared_ptr<ArrayAccessExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_expression: // array_expression
        value.YY_MOVE_OR_COPY< std::shared_ptr<ArrayExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_type: // array_type
        value.YY_MOVE_OR_COPY< std::shared_ptr<ArrayTypeNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call: // call
        value.YY_MOVE_OR_COPY< std::shared_ptr<CallExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constant: // constant
        value.YY_MOVE_OR_COPY< std::shared_ptr<ConstantExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_break: // break
      case symbol_kind::S_continue: // continue
        value.YY_MOVE_OR_COPY< std::shared_ptr<ControlStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.YY_MOVE_OR_COPY< std::shared_ptr<DeclarationStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_entry: // entry
        value.YY_MOVE_OR_COPY< std::shared_ptr<EntryNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
        value.YY_MOVE_OR_COPY< std::shared_ptr<ExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for: // for
        value.YY_MOVE_OR_COPY< std::shared_ptr<ForStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if: // if
      case symbol_kind::S_else: // else
        value.YY_MOVE_OR_COPY< std::shared_ptr<IfStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_return: // return
        value.YY_MOVE_OR_COPY< std::shared_ptr<ReturnStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.YY_MOVE_OR_COPY< std::shared_ptr<StatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_compound: // statement_compound
      case symbol_kind::S_statements: // statements
        value.YY_MOVE_OR_COPY< std::shared_ptr<StatementsNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< std::shared_ptr<TypeNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while: // while
        value.YY_MOVE_OR_COPY< std::shared_ptr<WhileStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CA_IDENTIFIER: // CA_IDENTIFIER
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_element: // array_element
      case symbol_kind::S_array_indices: // array_indices
      case symbol_kind::S_params: // params
        value.YY_MOVE_OR_COPY< std::vector<std::shared_ptr<ExpressionNode>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  CarlosParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_CA_CHAR_CONST: // CA_CHAR_CONST
        value.move< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CA_FLOAT_CONST: // CA_FLOAT_CONST
        value.move< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CA_INT_CONST: // CA_INT_CONST
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_access: // array_access
        value.move< std::shared_ptr<ArrayAccessExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_expression: // array_expression
        value.move< std::shared_ptr<ArrayExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_type: // array_type
        value.move< std::shared_ptr<ArrayTypeNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call: // call
        value.move< std::shared_ptr<CallExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constant: // constant
        value.move< std::shared_ptr<ConstantExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_break: // break
      case symbol_kind::S_continue: // continue
        value.move< std::shared_ptr<ControlStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< std::shared_ptr<DeclarationStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_entry: // entry
        value.move< std::shared_ptr<EntryNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
        value.move< std::shared_ptr<ExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for: // for
        value.move< std::shared_ptr<ForStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if: // if
      case symbol_kind::S_else: // else
        value.move< std::shared_ptr<IfStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_return: // return
        value.move< std::shared_ptr<ReturnStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.move< std::shared_ptr<StatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_compound: // statement_compound
      case symbol_kind::S_statements: // statements
        value.move< std::shared_ptr<StatementsNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.move< std::shared_ptr<TypeNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while: // while
        value.move< std::shared_ptr<WhileStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CA_IDENTIFIER: // CA_IDENTIFIER
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_element: // array_element
      case symbol_kind::S_array_indices: // array_indices
      case symbol_kind::S_params: // params
        value.move< std::vector<std::shared_ptr<ExpressionNode>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  CarlosParser::stack_symbol_type&
  CarlosParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_CA_CHAR_CONST: // CA_CHAR_CONST
        value.copy< char > (that.value);
        break;

      case symbol_kind::S_CA_FLOAT_CONST: // CA_FLOAT_CONST
        value.copy< float > (that.value);
        break;

      case symbol_kind::S_CA_INT_CONST: // CA_INT_CONST
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_array_access: // array_access
        value.copy< std::shared_ptr<ArrayAccessExpressionNode> > (that.value);
        break;

      case symbol_kind::S_array_expression: // array_expression
        value.copy< std::shared_ptr<ArrayExpressionNode> > (that.value);
        break;

      case symbol_kind::S_array_type: // array_type
        value.copy< std::shared_ptr<ArrayTypeNode> > (that.value);
        break;

      case symbol_kind::S_call: // call
        value.copy< std::shared_ptr<CallExpressionNode> > (that.value);
        break;

      case symbol_kind::S_constant: // constant
        value.copy< std::shared_ptr<ConstantExpressionNode> > (that.value);
        break;

      case symbol_kind::S_break: // break
      case symbol_kind::S_continue: // continue
        value.copy< std::shared_ptr<ControlStatementNode> > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< std::shared_ptr<DeclarationStatementNode> > (that.value);
        break;

      case symbol_kind::S_entry: // entry
        value.copy< std::shared_ptr<EntryNode> > (that.value);
        break;

      case symbol_kind::S_expression: // expression
        value.copy< std::shared_ptr<ExpressionNode> > (that.value);
        break;

      case symbol_kind::S_for: // for
        value.copy< std::shared_ptr<ForStatementNode> > (that.value);
        break;

      case symbol_kind::S_if: // if
      case symbol_kind::S_else: // else
        value.copy< std::shared_ptr<IfStatementNode> > (that.value);
        break;

      case symbol_kind::S_return: // return
        value.copy< std::shared_ptr<ReturnStatementNode> > (that.value);
        break;

      case symbol_kind::S_statement: // statement
        value.copy< std::shared_ptr<StatementNode> > (that.value);
        break;

      case symbol_kind::S_statement_compound: // statement_compound
      case symbol_kind::S_statements: // statements
        value.copy< std::shared_ptr<StatementsNode> > (that.value);
        break;

      case symbol_kind::S_type: // type
        value.copy< std::shared_ptr<TypeNode> > (that.value);
        break;

      case symbol_kind::S_while: // while
        value.copy< std::shared_ptr<WhileStatementNode> > (that.value);
        break;

      case symbol_kind::S_CA_IDENTIFIER: // CA_IDENTIFIER
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_array_element: // array_element
      case symbol_kind::S_array_indices: // array_indices
      case symbol_kind::S_params: // params
        value.copy< std::vector<std::shared_ptr<ExpressionNode>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  CarlosParser::stack_symbol_type&
  CarlosParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_CA_CHAR_CONST: // CA_CHAR_CONST
        value.move< char > (that.value);
        break;

      case symbol_kind::S_CA_FLOAT_CONST: // CA_FLOAT_CONST
        value.move< float > (that.value);
        break;

      case symbol_kind::S_CA_INT_CONST: // CA_INT_CONST
        value.move< int > (that.value);
        break;

      case symbol_kind::S_array_access: // array_access
        value.move< std::shared_ptr<ArrayAccessExpressionNode> > (that.value);
        break;

      case symbol_kind::S_array_expression: // array_expression
        value.move< std::shared_ptr<ArrayExpressionNode> > (that.value);
        break;

      case symbol_kind::S_array_type: // array_type
        value.move< std::shared_ptr<ArrayTypeNode> > (that.value);
        break;

      case symbol_kind::S_call: // call
        value.move< std::shared_ptr<CallExpressionNode> > (that.value);
        break;

      case symbol_kind::S_constant: // constant
        value.move< std::shared_ptr<ConstantExpressionNode> > (that.value);
        break;

      case symbol_kind::S_break: // break
      case symbol_kind::S_continue: // continue
        value.move< std::shared_ptr<ControlStatementNode> > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< std::shared_ptr<DeclarationStatementNode> > (that.value);
        break;

      case symbol_kind::S_entry: // entry
        value.move< std::shared_ptr<EntryNode> > (that.value);
        break;

      case symbol_kind::S_expression: // expression
        value.move< std::shared_ptr<ExpressionNode> > (that.value);
        break;

      case symbol_kind::S_for: // for
        value.move< std::shared_ptr<ForStatementNode> > (that.value);
        break;

      case symbol_kind::S_if: // if
      case symbol_kind::S_else: // else
        value.move< std::shared_ptr<IfStatementNode> > (that.value);
        break;

      case symbol_kind::S_return: // return
        value.move< std::shared_ptr<ReturnStatementNode> > (that.value);
        break;

      case symbol_kind::S_statement: // statement
        value.move< std::shared_ptr<StatementNode> > (that.value);
        break;

      case symbol_kind::S_statement_compound: // statement_compound
      case symbol_kind::S_statements: // statements
        value.move< std::shared_ptr<StatementsNode> > (that.value);
        break;

      case symbol_kind::S_type: // type
        value.move< std::shared_ptr<TypeNode> > (that.value);
        break;

      case symbol_kind::S_while: // while
        value.move< std::shared_ptr<WhileStatementNode> > (that.value);
        break;

      case symbol_kind::S_CA_IDENTIFIER: // CA_IDENTIFIER
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_array_element: // array_element
      case symbol_kind::S_array_indices: // array_indices
      case symbol_kind::S_params: // params
        value.move< std::vector<std::shared_ptr<ExpressionNode>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  CarlosParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  CarlosParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  CarlosParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  CarlosParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  CarlosParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  CarlosParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  CarlosParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  CarlosParser::debug_level_type
  CarlosParser::debug_level () const
  {
    return yydebug_;
  }

  void
  CarlosParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  CarlosParser::state_type
  CarlosParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  CarlosParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  CarlosParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  CarlosParser::operator() ()
  {
    return parse ();
  }

  int
  CarlosParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_CA_CHAR_CONST: // CA_CHAR_CONST
        yylhs.value.emplace< char > ();
        break;

      case symbol_kind::S_CA_FLOAT_CONST: // CA_FLOAT_CONST
        yylhs.value.emplace< float > ();
        break;

      case symbol_kind::S_CA_INT_CONST: // CA_INT_CONST
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_array_access: // array_access
        yylhs.value.emplace< std::shared_ptr<ArrayAccessExpressionNode> > ();
        break;

      case symbol_kind::S_array_expression: // array_expression
        yylhs.value.emplace< std::shared_ptr<ArrayExpressionNode> > ();
        break;

      case symbol_kind::S_array_type: // array_type
        yylhs.value.emplace< std::shared_ptr<ArrayTypeNode> > ();
        break;

      case symbol_kind::S_call: // call
        yylhs.value.emplace< std::shared_ptr<CallExpressionNode> > ();
        break;

      case symbol_kind::S_constant: // constant
        yylhs.value.emplace< std::shared_ptr<ConstantExpressionNode> > ();
        break;

      case symbol_kind::S_break: // break
      case symbol_kind::S_continue: // continue
        yylhs.value.emplace< std::shared_ptr<ControlStatementNode> > ();
        break;

      case symbol_kind::S_declaration: // declaration
        yylhs.value.emplace< std::shared_ptr<DeclarationStatementNode> > ();
        break;

      case symbol_kind::S_entry: // entry
        yylhs.value.emplace< std::shared_ptr<EntryNode> > ();
        break;

      case symbol_kind::S_expression: // expression
        yylhs.value.emplace< std::shared_ptr<ExpressionNode> > ();
        break;

      case symbol_kind::S_for: // for
        yylhs.value.emplace< std::shared_ptr<ForStatementNode> > ();
        break;

      case symbol_kind::S_if: // if
      case symbol_kind::S_else: // else
        yylhs.value.emplace< std::shared_ptr<IfStatementNode> > ();
        break;

      case symbol_kind::S_return: // return
        yylhs.value.emplace< std::shared_ptr<ReturnStatementNode> > ();
        break;

      case symbol_kind::S_statement: // statement
        yylhs.value.emplace< std::shared_ptr<StatementNode> > ();
        break;

      case symbol_kind::S_statement_compound: // statement_compound
      case symbol_kind::S_statements: // statements
        yylhs.value.emplace< std::shared_ptr<StatementsNode> > ();
        break;

      case symbol_kind::S_type: // type
        yylhs.value.emplace< std::shared_ptr<TypeNode> > ();
        break;

      case symbol_kind::S_while: // while
        yylhs.value.emplace< std::shared_ptr<WhileStatementNode> > ();
        break;

      case symbol_kind::S_CA_IDENTIFIER: // CA_IDENTIFIER
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_array_element: // array_element
      case symbol_kind::S_array_indices: // array_indices
      case symbol_kind::S_params: // params
        yylhs.value.emplace< std::vector<std::shared_ptr<ExpressionNode>> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: entry
#line 82 "carlos.ypp"
                 {
                root = std::make_shared<ProgramNode>(std::move(yystack_[0].value.as < std::shared_ptr<EntryNode> > ()));
            }
#line 990 "carlos.parser.cpp"
    break;

  case 3: // entry: CA_ENTRY statement_compound
#line 86 "carlos.ypp"
                                     {
                yylhs.value.as < std::shared_ptr<EntryNode> > () = std::make_shared<EntryNode>(std::move(yystack_[0].value.as < std::shared_ptr<StatementsNode> > ()));
            }
#line 998 "carlos.parser.cpp"
    break;

  case 4: // statement_compound: CA_LBRACE statements CA_RBRACE
#line 91 "carlos.ypp"
                                                     { yylhs.value.as < std::shared_ptr<StatementsNode> > () = std::move(yystack_[1].value.as < std::shared_ptr<StatementsNode> > ()); }
#line 1004 "carlos.parser.cpp"
    break;

  case 5: // statements: statements statement
#line 94 "carlos.ypp"
                                   {
               auto temp = std::move(yystack_[1].value.as < std::shared_ptr<StatementsNode> > ());
               temp->statements.push_back(std::move(yystack_[0].value.as < std::shared_ptr<StatementNode> > ()));
               yylhs.value.as < std::shared_ptr<StatementsNode> > () = std::move(temp);
            }
#line 1014 "carlos.parser.cpp"
    break;

  case 6: // statements: statements statement_compound
#line 99 "carlos.ypp"
                                            {
               auto temp = std::move(yystack_[1].value.as < std::shared_ptr<StatementsNode> > ());
               temp->statements.push_back(std::move(yystack_[0].value.as < std::shared_ptr<StatementsNode> > ()));
               yylhs.value.as < std::shared_ptr<StatementsNode> > () = std::move(temp);
            }
#line 1024 "carlos.parser.cpp"
    break;

  case 7: // statements: %empty
#line 104 "carlos.ypp"
                          { if (!yylhs.value.as < std::shared_ptr<StatementsNode> > ()) yylhs.value.as < std::shared_ptr<StatementsNode> > () = std::make_shared<StatementsNode>(); }
#line 1030 "carlos.parser.cpp"
    break;

  case 12: // statement: declaration semicolon
#line 115 "carlos.ypp"
                                   { yylhs.value.as < std::shared_ptr<StatementNode> > () = std::move(yystack_[1].value.as < std::shared_ptr<DeclarationStatementNode> > ()); }
#line 1036 "carlos.parser.cpp"
    break;

  case 13: // statement: expression semicolon
#line 116 "carlos.ypp"
                                   { yylhs.value.as < std::shared_ptr<StatementNode> > () = std::make_shared<ExpressionStatementNode>(std::move(yystack_[1].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1042 "carlos.parser.cpp"
    break;

  case 14: // statement: if opt_semicolon
#line 117 "carlos.ypp"
                               { yylhs.value.as < std::shared_ptr<StatementNode> > () = std::move(yystack_[1].value.as < std::shared_ptr<IfStatementNode> > ()); }
#line 1048 "carlos.parser.cpp"
    break;

  case 15: // statement: while opt_semicolon
#line 118 "carlos.ypp"
                                  { yylhs.value.as < std::shared_ptr<StatementNode> > () = std::move(yystack_[1].value.as < std::shared_ptr<WhileStatementNode> > ()); }
#line 1054 "carlos.parser.cpp"
    break;

  case 16: // statement: for opt_semicolon
#line 119 "carlos.ypp"
                                { yylhs.value.as < std::shared_ptr<StatementNode> > () = std::move(yystack_[1].value.as < std::shared_ptr<ForStatementNode> > ()); }
#line 1060 "carlos.parser.cpp"
    break;

  case 17: // statement: break semicolon
#line 120 "carlos.ypp"
                              { yylhs.value.as < std::shared_ptr<StatementNode> > () = std::move(yystack_[1].value.as < std::shared_ptr<ControlStatementNode> > ()); }
#line 1066 "carlos.parser.cpp"
    break;

  case 18: // statement: continue semicolon
#line 121 "carlos.ypp"
                                 { yylhs.value.as < std::shared_ptr<StatementNode> > () = std::move(yystack_[1].value.as < std::shared_ptr<ControlStatementNode> > ()); }
#line 1072 "carlos.parser.cpp"
    break;

  case 19: // statement: return semicolon
#line 122 "carlos.ypp"
                               { yylhs.value.as < std::shared_ptr<StatementNode> > () = std::move(yystack_[1].value.as < std::shared_ptr<ReturnStatementNode> > ()); }
#line 1078 "carlos.parser.cpp"
    break;

  case 20: // type: CA_BOOL
#line 125 "carlos.ypp"
                { yylhs.value.as < std::shared_ptr<TypeNode> > () = std::make_shared<BasicTypeNode>("bool"); }
#line 1084 "carlos.parser.cpp"
    break;

  case 21: // type: CA_INT32
#line 126 "carlos.ypp"
                       { yylhs.value.as < std::shared_ptr<TypeNode> > () = std::make_shared<BasicTypeNode>("i32"); }
#line 1090 "carlos.parser.cpp"
    break;

  case 22: // type: CA_FLOAT32
#line 127 "carlos.ypp"
                         { yylhs.value.as < std::shared_ptr<TypeNode> > () = std::make_shared<BasicTypeNode>("f32"); }
#line 1096 "carlos.parser.cpp"
    break;

  case 23: // type: CA_CHAR
#line 128 "carlos.ypp"
                      { yylhs.value.as < std::shared_ptr<TypeNode> > () = std::make_shared<BasicTypeNode>("char"); }
#line 1102 "carlos.parser.cpp"
    break;

  case 24: // type: array_type
#line 129 "carlos.ypp"
                         { yylhs.value.as < std::shared_ptr<TypeNode> > () = std::move(yystack_[0].value.as < std::shared_ptr<ArrayTypeNode> > ()); }
#line 1108 "carlos.parser.cpp"
    break;

  case 25: // constant: CA_INT_CONST
#line 132 "carlos.ypp"
                         { yylhs.value.as < std::shared_ptr<ConstantExpressionNode> > () = std::make_shared<ConstantExpressionNode>(yystack_[0].value.as < int > ()); }
#line 1114 "carlos.parser.cpp"
    break;

  case 26: // constant: CA_FLOAT_CONST
#line 133 "carlos.ypp"
                             { yylhs.value.as < std::shared_ptr<ConstantExpressionNode> > () = std::make_shared<ConstantExpressionNode>(yystack_[0].value.as < float > ()); }
#line 1120 "carlos.parser.cpp"
    break;

  case 27: // constant: CA_CHAR_CONST
#line 134 "carlos.ypp"
                            { yylhs.value.as < std::shared_ptr<ConstantExpressionNode> > () = std::make_shared<ConstantExpressionNode>(yystack_[0].value.as < char > ()); }
#line 1126 "carlos.parser.cpp"
    break;

  case 28: // constant: CA_TRUE
#line 135 "carlos.ypp"
                      { yylhs.value.as < std::shared_ptr<ConstantExpressionNode> > () = std::make_shared<ConstantExpressionNode>(true); }
#line 1132 "carlos.parser.cpp"
    break;

  case 29: // constant: CA_FALSE
#line 136 "carlos.ypp"
                       { yylhs.value.as < std::shared_ptr<ConstantExpressionNode> > () = std::make_shared<ConstantExpressionNode>(false); }
#line 1138 "carlos.parser.cpp"
    break;

  case 30: // array_type: CA_LBRACKET type CA_SEMICOLON expression CA_RBRACKET
#line 138 "carlos.ypp"
                                                                   {
                yylhs.value.as < std::shared_ptr<ArrayTypeNode> > () = std::make_shared<ArrayTypeNode>(std::move(yystack_[3].value.as < std::shared_ptr<TypeNode> > ()), std::move(yystack_[1].value.as < std::shared_ptr<ExpressionNode> > ()));
            }
#line 1146 "carlos.parser.cpp"
    break;

  case 31: // array_element: array_element CA_COMMA expression
#line 143 "carlos.ypp"
                                                   { auto temp = std::move(yystack_[2].value.as < std::vector<std::shared_ptr<ExpressionNode>> > ()); temp.push_back(std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); yylhs.value.as < std::vector<std::shared_ptr<ExpressionNode>> > () = std::move(temp); }
#line 1152 "carlos.parser.cpp"
    break;

  case 32: // array_element: expression
#line 144 "carlos.ypp"
                         { yylhs.value.as < std::vector<std::shared_ptr<ExpressionNode>> > ().push_back(std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1158 "carlos.parser.cpp"
    break;

  case 33: // array_expression: CA_LBRACKET expression CA_SEMICOLON expression CA_RBRACKET
#line 147 "carlos.ypp"
                                                                               {
                yylhs.value.as < std::shared_ptr<ArrayExpressionNode> > () = std::make_shared<ArrayExpressionNode>(std::move(yystack_[3].value.as < std::shared_ptr<ExpressionNode> > ()), std::move(yystack_[1].value.as < std::shared_ptr<ExpressionNode> > ()));
            }
#line 1166 "carlos.parser.cpp"
    break;

  case 34: // array_expression: CA_LBRACKET array_element CA_RBRACKET
#line 150 "carlos.ypp"
                                                    {
                yylhs.value.as < std::shared_ptr<ArrayExpressionNode> > () = std::make_shared<ArrayExpressionNode>(std::move(yystack_[1].value.as < std::vector<std::shared_ptr<ExpressionNode>> > ()));
            }
#line 1174 "carlos.parser.cpp"
    break;

  case 35: // array_indices: array_indices CA_LBRACKET expression CA_RBRACKET
#line 155 "carlos.ypp"
                                                                  { auto temp = std::move(yystack_[3].value.as < std::vector<std::shared_ptr<ExpressionNode>> > ()); temp.push_back(std::move(yystack_[1].value.as < std::shared_ptr<ExpressionNode> > ())); yylhs.value.as < std::vector<std::shared_ptr<ExpressionNode>> > () = std::move(temp); }
#line 1180 "carlos.parser.cpp"
    break;

  case 36: // array_indices: CA_LBRACKET expression CA_RBRACKET
#line 156 "carlos.ypp"
                                                 { yylhs.value.as < std::vector<std::shared_ptr<ExpressionNode>> > ().push_back(std::move(yystack_[1].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1186 "carlos.parser.cpp"
    break;

  case 37: // array_access: CA_IDENTIFIER array_indices
#line 159 "carlos.ypp"
                                            {
                auto identifier = std::make_shared<IdentifierExpressionNode>(yystack_[1].value.as < std::string > ());
                yylhs.value.as < std::shared_ptr<ArrayAccessExpressionNode> > () = std::make_shared<ArrayAccessExpressionNode>(std::move(identifier), std::move(yystack_[0].value.as < std::vector<std::shared_ptr<ExpressionNode>> > ()));
            }
#line 1195 "carlos.parser.cpp"
    break;

  case 38: // declaration: CA_LET CA_IDENTIFIER CA_COLON type
#line 165 "carlos.ypp"
                                                  {
                auto identifier = std::make_shared<IdentifierExpressionNode>(yystack_[2].value.as < std::string > ());
                yylhs.value.as < std::shared_ptr<DeclarationStatementNode> > () = std::make_shared<DeclarationStatementNode>(std::move(identifier), std::move(yystack_[0].value.as < std::shared_ptr<TypeNode> > ()), false, nullptr);
            }
#line 1204 "carlos.parser.cpp"
    break;

  case 39: // declaration: CA_LET CA_MUT CA_IDENTIFIER CA_COLON type
#line 169 "carlos.ypp"
                                                        {
                auto identifier = std::make_shared<IdentifierExpressionNode>(yystack_[2].value.as < std::string > ());
                yylhs.value.as < std::shared_ptr<DeclarationStatementNode> > () = std::make_shared<DeclarationStatementNode>(std::move(identifier), std::move(yystack_[0].value.as < std::shared_ptr<TypeNode> > ()), true, nullptr);
            }
#line 1213 "carlos.parser.cpp"
    break;

  case 40: // declaration: CA_LET CA_IDENTIFIER CA_COLON type CA_ASSIGN expression
#line 173 "carlos.ypp"
                                                                      {
                auto identifier = std::make_shared<IdentifierExpressionNode>(yystack_[4].value.as < std::string > ());
                yylhs.value.as < std::shared_ptr<DeclarationStatementNode> > () = std::make_shared<DeclarationStatementNode>(std::move(identifier), std::move(yystack_[2].value.as < std::shared_ptr<TypeNode> > ()), false, std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ()));
            }
#line 1222 "carlos.parser.cpp"
    break;

  case 41: // declaration: CA_LET CA_MUT CA_IDENTIFIER CA_COLON type CA_ASSIGN expression
#line 177 "carlos.ypp"
                                                                             {
                auto identifier = std::make_shared<IdentifierExpressionNode>(yystack_[4].value.as < std::string > ());
                yylhs.value.as < std::shared_ptr<DeclarationStatementNode> > () = std::make_shared<DeclarationStatementNode>(std::move(identifier), std::move(yystack_[2].value.as < std::shared_ptr<TypeNode> > ()), true, std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ()));
            }
#line 1231 "carlos.parser.cpp"
    break;

  case 42: // declaration: CA_LET CA_IDENTIFIER CA_ASSIGN expression
#line 181 "carlos.ypp"
                                                        {
                auto identifier = std::make_shared<IdentifierExpressionNode>(yystack_[2].value.as < std::string > ());
                yylhs.value.as < std::shared_ptr<DeclarationStatementNode> > () = std::make_shared<DeclarationStatementNode>(std::move(identifier), nullptr, false, std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ()));
            }
#line 1240 "carlos.parser.cpp"
    break;

  case 43: // declaration: CA_LET CA_MUT CA_IDENTIFIER CA_ASSIGN expression
#line 185 "carlos.ypp"
                                                               {
                auto identifier = std::make_shared<IdentifierExpressionNode>(yystack_[2].value.as < std::string > ());
                yylhs.value.as < std::shared_ptr<DeclarationStatementNode> > () = std::make_shared<DeclarationStatementNode>(std::move(identifier), nullptr, true, std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ()));
            }
#line 1249 "carlos.parser.cpp"
    break;

  case 44: // expression: constant
#line 191 "carlos.ypp"
                       { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::move(yystack_[0].value.as < std::shared_ptr<ConstantExpressionNode> > ()); }
#line 1255 "carlos.parser.cpp"
    break;

  case 45: // expression: CA_IDENTIFIER
#line 192 "carlos.ypp"
                            { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<IdentifierExpressionNode>(yystack_[0].value.as < std::string > ()); }
#line 1261 "carlos.parser.cpp"
    break;

  case 46: // expression: array_expression
#line 193 "carlos.ypp"
                               { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::move(yystack_[0].value.as < std::shared_ptr<ArrayExpressionNode> > ()); }
#line 1267 "carlos.parser.cpp"
    break;

  case 47: // expression: array_access
#line 194 "carlos.ypp"
                           { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::move(yystack_[0].value.as < std::shared_ptr<ArrayAccessExpressionNode> > ()); }
#line 1273 "carlos.parser.cpp"
    break;

  case 48: // expression: call
#line 195 "carlos.ypp"
                   { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::move(yystack_[0].value.as < std::shared_ptr<CallExpressionNode> > ()); }
#line 1279 "carlos.parser.cpp"
    break;

  case 49: // expression: expression CA_PLUS expression
#line 196 "carlos.ypp"
                                            { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "+", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1285 "carlos.parser.cpp"
    break;

  case 50: // expression: expression CA_MINUS expression
#line 197 "carlos.ypp"
                                             { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "-", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1291 "carlos.parser.cpp"
    break;

  case 51: // expression: expression CA_MUL expression
#line 198 "carlos.ypp"
                                           { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "*", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1297 "carlos.parser.cpp"
    break;

  case 52: // expression: expression CA_DIV expression
#line 199 "carlos.ypp"
                                           { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "/", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1303 "carlos.parser.cpp"
    break;

  case 53: // expression: expression CA_MOD expression
#line 200 "carlos.ypp"
                                           { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "%", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1309 "carlos.parser.cpp"
    break;

  case 54: // expression: expression CA_AND expression
#line 201 "carlos.ypp"
                                           { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "&&", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1315 "carlos.parser.cpp"
    break;

  case 55: // expression: expression CA_OR expression
#line 202 "carlos.ypp"
                                          { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "||", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1321 "carlos.parser.cpp"
    break;

  case 56: // expression: expression CA_EQ expression
#line 203 "carlos.ypp"
                                          { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "==", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1327 "carlos.parser.cpp"
    break;

  case 57: // expression: expression CA_NEQ expression
#line 204 "carlos.ypp"
                                           { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "!=", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1333 "carlos.parser.cpp"
    break;

  case 58: // expression: expression CA_LT expression
#line 205 "carlos.ypp"
                                          { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "<", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1339 "carlos.parser.cpp"
    break;

  case 59: // expression: expression CA_GT expression
#line 206 "carlos.ypp"
                                          { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), ">", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1345 "carlos.parser.cpp"
    break;

  case 60: // expression: expression CA_LTE expression
#line 207 "carlos.ypp"
                                           { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "<=", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1351 "carlos.parser.cpp"
    break;

  case 61: // expression: expression CA_GTE expression
#line 208 "carlos.ypp"
                                           { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), ">=", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1357 "carlos.parser.cpp"
    break;

  case 62: // expression: expression CA_RANGE expression
#line 209 "carlos.ypp"
                                             { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "..", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1363 "carlos.parser.cpp"
    break;

  case 63: // expression: expression CA_RANGE_INCLUSIVE expression
#line 210 "carlos.ypp"
                                                       { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "..=", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1369 "carlos.parser.cpp"
    break;

  case 64: // expression: expression CA_ASSIGN expression
#line 211 "carlos.ypp"
                                              { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "=", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1375 "carlos.parser.cpp"
    break;

  case 65: // expression: expression CA_PLUS_ASSIGN expression
#line 212 "carlos.ypp"
                                                   { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "+=", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1381 "carlos.parser.cpp"
    break;

  case 66: // expression: expression CA_MINUS_ASSIGN expression
#line 213 "carlos.ypp"
                                                    { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "-=", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1387 "carlos.parser.cpp"
    break;

  case 67: // expression: expression CA_MUL_ASSIGN expression
#line 214 "carlos.ypp"
                                                  { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "*=", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1393 "carlos.parser.cpp"
    break;

  case 68: // expression: expression CA_DIV_ASSIGN expression
#line 215 "carlos.ypp"
                                                  { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "/=", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1399 "carlos.parser.cpp"
    break;

  case 69: // expression: expression CA_MOD_ASSIGN expression
#line 216 "carlos.ypp"
                                                  { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<BinaryExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), "%=", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1405 "carlos.parser.cpp"
    break;

  case 70: // expression: expression CA_AS type
#line 217 "carlos.ypp"
                                    { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<CastExpressionNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), std::move(yystack_[0].value.as < std::shared_ptr<TypeNode> > ())); }
#line 1411 "carlos.parser.cpp"
    break;

  case 71: // expression: CA_LPAREN expression CA_RPAREN
#line 218 "carlos.ypp"
                                             { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::move(yystack_[1].value.as < std::shared_ptr<ExpressionNode> > ()); }
#line 1417 "carlos.parser.cpp"
    break;

  case 72: // expression: CA_NOT expression
#line 219 "carlos.ypp"
                                { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<UnaryExpressionNode>("!", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1423 "carlos.parser.cpp"
    break;

  case 73: // expression: CA_MINUS expression
#line 220 "carlos.ypp"
                                               { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<UnaryExpressionNode>("-", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1429 "carlos.parser.cpp"
    break;

  case 74: // expression: CA_PLUS expression
#line 221 "carlos.ypp"
                                              { yylhs.value.as < std::shared_ptr<ExpressionNode> > () = std::make_shared<UnaryExpressionNode>("+", std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1435 "carlos.parser.cpp"
    break;

  case 75: // params: params CA_COMMA expression
#line 224 "carlos.ypp"
                                     { auto temp = std::move(yystack_[2].value.as < std::vector<std::shared_ptr<ExpressionNode>> > ()); temp.push_back(std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); yylhs.value.as < std::vector<std::shared_ptr<ExpressionNode>> > () = std::move(temp); }
#line 1441 "carlos.parser.cpp"
    break;

  case 76: // params: expression
#line 225 "carlos.ypp"
                         { yylhs.value.as < std::vector<std::shared_ptr<ExpressionNode>> > ().push_back(std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1447 "carlos.parser.cpp"
    break;

  case 77: // call: CA_IDENTIFIER CA_LPAREN params CA_RPAREN
#line 228 "carlos.ypp"
                                                 { yylhs.value.as < std::shared_ptr<CallExpressionNode> > () = std::make_shared<CallExpressionNode>(std::move(yystack_[3].value.as < std::string > ()), std::move(yystack_[1].value.as < std::vector<std::shared_ptr<ExpressionNode>> > ())); }
#line 1453 "carlos.parser.cpp"
    break;

  case 78: // if: CA_IF expression statement_compound else
#line 231 "carlos.ypp"
                                               {
                yylhs.value.as < std::shared_ptr<IfStatementNode> > () = std::make_shared<IfStatementNode>(std::move(yystack_[2].value.as < std::shared_ptr<ExpressionNode> > ()), std::move(yystack_[1].value.as < std::shared_ptr<StatementsNode> > ()), std::move(yystack_[0].value.as < std::shared_ptr<IfStatementNode> > ()));
            }
#line 1461 "carlos.parser.cpp"
    break;

  case 79: // else: CA_ELSE if
#line 236 "carlos.ypp"
                   { yylhs.value.as < std::shared_ptr<IfStatementNode> > () = std::move(yystack_[0].value.as < std::shared_ptr<IfStatementNode> > ()); }
#line 1467 "carlos.parser.cpp"
    break;

  case 80: // else: CA_ELSE statement_compound
#line 237 "carlos.ypp"
                                         {
                yylhs.value.as < std::shared_ptr<IfStatementNode> > () = std::make_shared<IfStatementNode>(nullptr, std::move(yystack_[0].value.as < std::shared_ptr<StatementsNode> > ()), nullptr);
            }
#line 1475 "carlos.parser.cpp"
    break;

  case 81: // else: %empty
#line 240 "carlos.ypp"
                          { yylhs.value.as < std::shared_ptr<IfStatementNode> > () = nullptr; }
#line 1481 "carlos.parser.cpp"
    break;

  case 82: // while: CA_WHILE expression statement_compound
#line 243 "carlos.ypp"
                                                {
                yylhs.value.as < std::shared_ptr<WhileStatementNode> > () = std::make_shared<WhileStatementNode>(std::move(yystack_[1].value.as < std::shared_ptr<ExpressionNode> > ()), std::move(yystack_[0].value.as < std::shared_ptr<StatementsNode> > ()));
            }
#line 1489 "carlos.parser.cpp"
    break;

  case 83: // for: CA_FOR CA_IDENTIFIER CA_IN expression statement_compound
#line 248 "carlos.ypp"
                                                                {
                auto identifier = std::make_shared<IdentifierExpressionNode>(yystack_[3].value.as < std::string > ());
                yylhs.value.as < std::shared_ptr<ForStatementNode> > () = std::make_shared<ForStatementNode>(std::move(identifier), false, std::move(yystack_[1].value.as < std::shared_ptr<ExpressionNode> > ()), std::move(yystack_[0].value.as < std::shared_ptr<StatementsNode> > ()));
            }
#line 1498 "carlos.parser.cpp"
    break;

  case 84: // for: CA_FOR CA_MUT CA_IDENTIFIER CA_IN expression statement_compound
#line 252 "carlos.ypp"
                                                                              {
                auto identifier = std::make_shared<IdentifierExpressionNode>(yystack_[3].value.as < std::string > ());
                yylhs.value.as < std::shared_ptr<ForStatementNode> > () = std::make_shared<ForStatementNode>(std::move(identifier), true, std::move(yystack_[1].value.as < std::shared_ptr<ExpressionNode> > ()), std::move(yystack_[0].value.as < std::shared_ptr<StatementsNode> > ()));
            }
#line 1507 "carlos.parser.cpp"
    break;

  case 85: // break: CA_BREAK
#line 258 "carlos.ypp"
                  { yylhs.value.as < std::shared_ptr<ControlStatementNode> > () = std::make_shared<ControlStatementNode>("break"); }
#line 1513 "carlos.parser.cpp"
    break;

  case 86: // continue: CA_CONTINUE
#line 261 "carlos.ypp"
                        { yylhs.value.as < std::shared_ptr<ControlStatementNode> > () = std::make_shared<ControlStatementNode>("continue"); }
#line 1519 "carlos.parser.cpp"
    break;

  case 87: // return: CA_RETURN expression
#line 264 "carlos.ypp"
                               { yylhs.value.as < std::shared_ptr<ReturnStatementNode> > () = std::make_shared<ReturnStatementNode>(std::move(yystack_[0].value.as < std::shared_ptr<ExpressionNode> > ())); }
#line 1525 "carlos.parser.cpp"
    break;

  case 88: // return: CA_RETURN
#line 265 "carlos.ypp"
                        { yylhs.value.as < std::shared_ptr<ReturnStatementNode> > () = std::make_shared<ReturnStatementNode>(nullptr); }
#line 1531 "carlos.parser.cpp"
    break;


#line 1535 "carlos.parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  CarlosParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  CarlosParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  CarlosParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // CarlosParser::context.
  CarlosParser::context::context (const CarlosParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  CarlosParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  CarlosParser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  CarlosParser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char CarlosParser::yypact_ninf_ = -88;

  const signed char CarlosParser::yytable_ninf_ = -1;

  const short
  CarlosParser::yypact_[] =
  {
       0,   -10,    49,   -88,   -88,   -88,   -88,    96,     7,   138,
     138,   138,     9,   -88,   -88,   -88,   -88,   138,   138,   138,
     138,   -88,   138,   -88,   -88,   -88,   -34,   -88,   -88,   -88,
     -88,   -88,     4,   180,   -88,     4,     4,     4,     4,     4,
       4,   -15,     3,   476,   217,   217,    13,    73,   -88,   -88,
     -88,   254,   -24,   291,   138,   138,    45,   -88,    61,    16,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,    61,    61,   -88,   -88,   -88,    61,    61,    61,    42,
     138,    16,   101,   -88,    89,   138,   -88,   138,   -88,   138,
     476,    -7,   328,   138,   -88,   -88,   -88,   -88,   -88,    16,
     -88,   -88,    65,    65,    97,    97,    97,   140,    -8,   493,
     493,    71,    71,    71,    71,   476,   476,   476,   476,   476,
     476,   156,   156,   138,    16,   476,    74,    32,   -88,   138,
     217,   476,   365,   138,   -88,   -88,   402,    76,   476,    75,
     138,   -88,   -88,   217,   -88,   -88,   476,   -88,   138,   138,
     476,   -88,   439,   476,   -88
  };

  const signed char
  CarlosParser::yydefact_[] =
  {
       0,     0,     0,     2,     7,     3,     1,     0,     0,    88,
       0,     0,     0,    85,    86,    28,    29,     0,     0,     0,
       0,     4,     0,    25,    26,    27,    45,     6,     5,    44,
      46,    47,     0,     0,    48,    11,    11,    11,     0,     0,
       0,     0,     0,    87,     0,     0,     0,     0,    74,    73,
      72,     0,     0,    32,     0,     0,    37,     9,    12,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    13,    10,    14,    15,    16,    17,    18,    19,     0,
       0,     0,    81,    82,     0,     0,    71,     0,    34,     0,
      76,     0,     0,     0,     8,    20,    21,    22,    23,     0,
      70,    24,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    64,    65,    66,    67,    68,
      69,    62,    63,     0,     0,    42,    38,     0,    78,     0,
       0,    31,     0,     0,    77,    36,     0,     0,    43,    39,
       0,    80,    79,     0,    83,    33,    75,    35,     0,     0,
      40,    84,     0,    41,    30
  };

  const signed char
  CarlosParser::yypgoto_[] =
  {
     -88,   -88,   -88,    -2,   -88,    44,    -6,   -88,   -87,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,    -9,   -88,   -88,   -20,
     -88,   -88,   -88,   -88,   -88,   -88
  };

  const unsigned char
  CarlosParser::yydefgoto_[] =
  {
       0,     2,     3,     5,     7,    82,    83,    28,   110,    29,
     111,    52,    30,    56,    31,    32,    33,   101,    34,    35,
     138,    36,    37,    38,    39,    40
  };

  const unsigned char
  CarlosParser::yytable_[] =
  {
      43,    44,    45,     1,   136,    27,    59,    54,    48,    49,
      50,    51,    41,    53,    46,    97,    60,    61,    62,    63,
      64,    65,   147,    55,    67,    68,    69,    70,    71,    72,
      84,    85,   143,     4,    98,   144,   105,   106,   107,   108,
      10,    90,    92,    93,    57,   100,   102,   149,    91,     6,
      89,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,    42,   109,    47,     4,    58,    81,    94,    59,
     133,   135,    86,    87,    88,    59,   140,   134,   141,    95,
     142,    62,    63,    64,   146,    60,    61,    62,    63,    64,
       8,   104,   103,     9,    10,   139,    11,    12,    13,    14,
     137,    59,   150,   159,    15,    16,   158,   152,     0,     0,
      17,    18,     0,     0,   148,     0,     0,    19,     0,     0,
     153,     0,     0,     0,   156,   151,     0,    20,   154,     4,
      21,   160,     0,     0,     0,     0,     0,     0,     0,   162,
     163,   161,     0,    22,    59,     0,    15,    16,    23,    24,
      25,    26,    17,    18,    60,    61,    62,    63,    64,    19,
      59,     0,    67,    68,    69,    70,    71,    72,     0,    20,
      60,    61,    62,    63,    64,    65,    66,     0,    67,    68,
      69,    70,    71,    72,    59,    22,     0,     0,     0,     0,
      23,    24,    25,    26,    60,    61,    62,    63,    64,    65,
      66,     0,    67,    68,    69,    70,    71,    72,    73,     0,
      57,     0,     0,     0,     0,     0,    74,    75,    76,    77,
      78,    59,     0,     0,     0,     0,     0,     0,     0,    79,
      80,    60,    61,    62,    63,    64,    65,    66,     0,    67,
      68,    69,    70,    71,    72,    73,     0,     0,     0,     0,
       4,     0,     0,    74,    75,    76,    77,    78,    59,     0,
       0,     0,     0,     0,     0,     0,    79,    80,    60,    61,
      62,    63,    64,    65,    66,     0,    67,    68,    69,    70,
      71,    72,    73,     0,     0,     0,    96,     0,     0,     0,
      74,    75,    76,    77,    78,    59,     0,     0,     0,     0,
       0,     0,     0,    79,    80,    60,    61,    62,    63,    64,
      65,    66,     0,    67,    68,    69,    70,    71,    72,    73,
       0,    99,     0,     0,     0,     0,     0,    74,    75,    76,
      77,    78,    59,     0,     0,     0,     0,     0,     0,     0,
      79,    80,    60,    61,    62,    63,    64,    65,    66,     0,
      67,    68,    69,    70,    71,    72,    73,     0,     0,     0,
       0,     0,     0,     0,    74,    75,    76,    77,    78,    59,
       0,     0,     0,     0,     0,     0,   145,    79,    80,    60,
      61,    62,    63,    64,    65,    66,     0,    67,    68,    69,
      70,    71,    72,    73,     0,     0,     0,     0,     0,     0,
       0,    74,    75,    76,    77,    78,    59,     0,     0,     0,
       0,     0,     0,   155,    79,    80,    60,    61,    62,    63,
      64,    65,    66,     0,    67,    68,    69,    70,    71,    72,
      73,     0,     0,     0,     0,     0,     0,     0,    74,    75,
      76,    77,    78,    59,     0,     0,     0,     0,     0,     0,
     157,    79,    80,    60,    61,    62,    63,    64,    65,    66,
       0,    67,    68,    69,    70,    71,    72,    73,     0,     0,
       0,     0,     0,     0,     0,    74,    75,    76,    77,    78,
      59,     0,     0,     0,     0,     0,     0,   164,    79,    80,
      60,    61,    62,    63,    64,    65,    66,    59,    67,    68,
      69,    70,    71,    72,    73,     0,     0,    60,    61,    62,
      63,    64,    74,    75,    76,    77,    78,    69,    70,    71,
      72,     0,     0,     0,     0,    79,    80
  };

  const short
  CarlosParser::yycheck_[] =
  {
       9,    10,    11,     3,    91,     7,    14,    41,    17,    18,
      19,    20,     5,    22,     5,    39,    24,    25,    26,    27,
      28,    29,   109,    57,    32,    33,    34,    35,    36,    37,
      36,    37,    39,    43,    58,    42,    20,    21,    22,    23,
       8,    38,    44,    45,    40,    54,    55,   134,    45,     0,
      65,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    65,    57,    65,    43,    32,    33,    65,    14,
      38,    90,    38,    39,    40,    14,    95,    45,    97,    16,
      99,    26,    27,    28,   103,    24,    25,    26,    27,    28,
       4,    40,    57,     7,     8,    16,    10,    11,    12,    13,
       9,    14,    38,    38,    18,    19,    40,   137,    -1,    -1,
      24,    25,    -1,    -1,   133,    -1,    -1,    31,    -1,    -1,
     139,    -1,    -1,    -1,   143,   137,    -1,    41,   140,    43,
      44,   150,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   158,
     159,   153,    -1,    57,    14,    -1,    18,    19,    62,    63,
      64,    65,    24,    25,    24,    25,    26,    27,    28,    31,
      14,    -1,    32,    33,    34,    35,    36,    37,    -1,    41,
      24,    25,    26,    27,    28,    29,    30,    -1,    32,    33,
      34,    35,    36,    37,    14,    57,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    24,    25,    26,    27,    28,    29,
      30,    -1,    32,    33,    34,    35,    36,    37,    38,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    24,    25,    26,    27,    28,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      43,    -1,    -1,    46,    47,    48,    49,    50,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    24,    25,
      26,    27,    28,    29,    30,    -1,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    24,    25,    26,    27,    28,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    24,    25,    26,    27,    28,    29,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    24,
      25,    26,    27,    28,    29,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    24,    25,    26,    27,
      28,    29,    30,    -1,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      58,    59,    60,    24,    25,    26,    27,    28,    29,    30,
      -1,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,
      24,    25,    26,    27,    28,    29,    30,    14,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    24,    25,    26,
      27,    28,    46,    47,    48,    49,    50,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    59,    60
  };

  const signed char
  CarlosParser::yystos_[] =
  {
       0,     3,    69,    70,    43,    71,     0,    72,     4,     7,
       8,    10,    11,    12,    13,    18,    19,    24,    25,    31,
      41,    44,    57,    62,    63,    64,    65,    71,    75,    77,
      80,    82,    83,    84,    86,    87,    89,    90,    91,    92,
      93,     5,    65,    84,    84,    84,     5,    65,    84,    84,
      84,    84,    79,    84,    41,    57,    81,    40,    73,    14,
      24,    25,    26,    27,    28,    29,    30,    32,    33,    34,
      35,    36,    37,    38,    46,    47,    48,    49,    50,    59,
      60,    73,    73,    74,    74,    74,    73,    73,    73,    65,
      38,    45,    71,    71,    65,    16,    42,    39,    58,    40,
      84,    85,    84,    57,    40,    20,    21,    22,    23,    57,
      76,    78,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    38,    45,    84,    76,     9,    88,    16,
      84,    84,    84,    39,    42,    58,    84,    76,    84,    76,
      38,    71,    87,    84,    71,    58,    84,    58,    40,    38,
      84,    71,    84,    84,    58
  };

  const signed char
  CarlosParser::yyr1_[] =
  {
       0,    68,    69,    70,    71,    72,    72,    72,    73,    73,
      74,    74,    75,    75,    75,    75,    75,    75,    75,    75,
      76,    76,    76,    76,    76,    77,    77,    77,    77,    77,
      78,    79,    79,    80,    80,    81,    81,    82,    83,    83,
      83,    83,    83,    83,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    85,    85,    86,    87,    88,
      88,    88,    89,    90,    90,    91,    92,    93,    93
  };

  const signed char
  CarlosParser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     2,     2,     0,     2,     1,
       1,     0,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     3,     1,     5,     3,     4,     3,     2,     4,     5,
       6,     7,     4,     5,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     3,     1,     4,     4,     2,
       2,     0,     3,     5,     6,     1,     1,     2,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const CarlosParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "CA_ENTRY", "CA_LET",
  "CA_MUT", "CA_FN", "CA_RETURN", "CA_IF", "CA_ELSE", "CA_WHILE", "CA_FOR",
  "CA_BREAK", "CA_CONTINUE", "CA_AS", "CA_RETURN_TYPE", "CA_IN",
  "CA_CONST", "CA_TRUE", "CA_FALSE", "CA_BOOL", "CA_INT32", "CA_FLOAT32",
  "CA_CHAR", "CA_PLUS", "CA_MINUS", "CA_MUL", "CA_DIV", "CA_MOD", "CA_AND",
  "CA_OR", "CA_NOT", "CA_EQ", "CA_NEQ", "CA_LT", "CA_GT", "CA_LTE",
  "CA_GTE", "CA_ASSIGN", "CA_COMMA", "CA_SEMICOLON", "CA_LPAREN",
  "CA_RPAREN", "CA_LBRACE", "CA_RBRACE", "CA_COLON", "CA_PLUS_ASSIGN",
  "CA_MINUS_ASSIGN", "CA_MUL_ASSIGN", "CA_DIV_ASSIGN", "CA_MOD_ASSIGN",
  "CA_BITWISE_AND", "CA_BITWISE_OR", "CA_BITWISE_XOR", "CA_BITWISE_NOT",
  "CA_BITWISE_LSHIFT", "CA_BITWISE_RSHIFT", "CA_LBRACKET", "CA_RBRACKET",
  "CA_RANGE", "CA_RANGE_INCLUSIVE", "CA_DOT", "CA_INT_CONST",
  "CA_FLOAT_CONST", "CA_CHAR_CONST", "CA_IDENTIFIER", "CA_NEG", "CA_POS",
  "$accept", "program", "entry", "statement_compound", "statements",
  "semicolon", "opt_semicolon", "statement", "type", "constant",
  "array_type", "array_element", "array_expression", "array_indices",
  "array_access", "declaration", "expression", "params", "call", "if",
  "else", "while", "for", "break", "continue", "return", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  CarlosParser::yyrline_[] =
  {
       0,    82,    82,    86,    91,    94,    99,   104,   107,   108,
     111,   112,   115,   116,   117,   118,   119,   120,   121,   122,
     125,   126,   127,   128,   129,   132,   133,   134,   135,   136,
     138,   143,   144,   147,   150,   155,   156,   159,   165,   169,
     173,   177,   181,   185,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   224,   225,   228,   231,   236,
     237,   240,   243,   248,   252,   258,   261,   264,   265
  };

  void
  CarlosParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  CarlosParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 17 "carlos.ypp"
} // carlos
#line 2193 "carlos.parser.cpp"

#line 267 "carlos.ypp"


void carlos::CarlosParser::error(const Location &loc, const std::string &msg) {
  std::cerr << "Error at " << loc << ": " << msg << std::endl;
}
