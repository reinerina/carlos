// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file carlos.parser.h
 ** Define the carlos::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_CARLOS_PARSER_H_INCLUDED
# define YY_YY_CARLOS_PARSER_H_INCLUDED
// "%code requires" blocks.
#line 20 "carlos.ypp"

  #include <string>
  #include <memory>
  #include <vector>
  #include "ast.h"
  #include "location.h"
  namespace carlos {
    class CarlosLexer;
  }

#line 60 "carlos.parser.h"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif

#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 17 "carlos.ypp"
namespace carlos {
#line 201 "carlos.parser.h"




  /// A Bison parser.
  class CarlosParser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // CA_CHAR_CONST
      char dummy1[sizeof (char)];

      // CA_FLOAT_CONST
      char dummy2[sizeof (float)];

      // CA_INT_CONST
      char dummy3[sizeof (int)];

      // array_access
      char dummy4[sizeof (std::shared_ptr<ArrayAccessExpressionNode>)];

      // array_expression
      char dummy5[sizeof (std::shared_ptr<ArrayExpressionNode>)];

      // array_type
      char dummy6[sizeof (std::shared_ptr<ArrayTypeNode>)];

      // constant
      char dummy7[sizeof (std::shared_ptr<ConstantExpressionNode>)];

      // break
      // continue
      char dummy8[sizeof (std::shared_ptr<ControlStatementNode>)];

      // declaration
      char dummy9[sizeof (std::shared_ptr<DeclarationStatementNode>)];

      // entry
      char dummy10[sizeof (std::shared_ptr<EntryNode>)];

      // expression
      char dummy11[sizeof (std::shared_ptr<ExpressionNode>)];

      // for
      char dummy12[sizeof (std::shared_ptr<ForStatementNode>)];

      // if
      // else
      char dummy13[sizeof (std::shared_ptr<IfStatementNode>)];

      // return
      char dummy14[sizeof (std::shared_ptr<ReturnStatementNode>)];

      // statement
      char dummy15[sizeof (std::shared_ptr<StatementNode>)];

      // statement_compound
      // statements
      char dummy16[sizeof (std::shared_ptr<StatementsNode>)];

      // type
      char dummy17[sizeof (std::shared_ptr<TypeNode>)];

      // while
      char dummy18[sizeof (std::shared_ptr<WhileStatementNode>)];

      // CA_IDENTIFIER
      char dummy19[sizeof (std::string)];

      // array_element
      // array_indices
      char dummy20[sizeof (std::vector<std::shared_ptr<ExpressionNode>>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef Location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 1025,                // "invalid token"
    CA_ENTRY = 1024,               // CA_ENTRY
    CA_LET = 1026,                 // CA_LET
    CA_MUT = 1027,                 // CA_MUT
    CA_FN = 1028,                  // CA_FN
    CA_RETURN = 1029,              // CA_RETURN
    CA_IF = 1030,                  // CA_IF
    CA_ELSE = 1031,                // CA_ELSE
    CA_WHILE = 1032,               // CA_WHILE
    CA_FOR = 1033,                 // CA_FOR
    CA_BREAK = 1034,               // CA_BREAK
    CA_CONTINUE = 1035,            // CA_CONTINUE
    CA_AS = 1036,                  // CA_AS
    CA_RETURN_TYPE = 1037,         // CA_RETURN_TYPE
    CA_IN = 1038,                  // CA_IN
    CA_CONST = 1039,               // CA_CONST
    CA_TRUE = 1040,                // CA_TRUE
    CA_FALSE = 1041,               // CA_FALSE
    CA_BOOL = 1042,                // CA_BOOL
    CA_INT32 = 1043,               // CA_INT32
    CA_FLOAT32 = 1044,             // CA_FLOAT32
    CA_CHAR = 1045,                // CA_CHAR
    CA_PLUS = 1046,                // CA_PLUS
    CA_MINUS = 1047,               // CA_MINUS
    CA_MUL = 1048,                 // CA_MUL
    CA_DIV = 1049,                 // CA_DIV
    CA_MOD = 1050,                 // CA_MOD
    CA_AND = 1051,                 // CA_AND
    CA_OR = 1052,                  // CA_OR
    CA_NOT = 1053,                 // CA_NOT
    CA_EQ = 1054,                  // CA_EQ
    CA_NEQ = 1055,                 // CA_NEQ
    CA_LT = 1056,                  // CA_LT
    CA_GT = 1057,                  // CA_GT
    CA_LTE = 1058,                 // CA_LTE
    CA_GTE = 1059,                 // CA_GTE
    CA_ASSIGN = 1060,              // CA_ASSIGN
    CA_COMMA = 1061,               // CA_COMMA
    CA_SEMICOLON = 1062,           // CA_SEMICOLON
    CA_LPAREN = 1063,              // CA_LPAREN
    CA_RPAREN = 1064,              // CA_RPAREN
    CA_LBRACE = 1065,              // CA_LBRACE
    CA_RBRACE = 1066,              // CA_RBRACE
    CA_COLON = 1067,               // CA_COLON
    CA_PLUS_ASSIGN = 1068,         // CA_PLUS_ASSIGN
    CA_MINUS_ASSIGN = 1069,        // CA_MINUS_ASSIGN
    CA_MUL_ASSIGN = 1070,          // CA_MUL_ASSIGN
    CA_DIV_ASSIGN = 1071,          // CA_DIV_ASSIGN
    CA_MOD_ASSIGN = 1072,          // CA_MOD_ASSIGN
    CA_BITWISE_AND = 1073,         // CA_BITWISE_AND
    CA_BITWISE_OR = 1074,          // CA_BITWISE_OR
    CA_BITWISE_XOR = 1075,         // CA_BITWISE_XOR
    CA_BITWISE_NOT = 1076,         // CA_BITWISE_NOT
    CA_BITWISE_LSHIFT = 1077,      // CA_BITWISE_LSHIFT
    CA_BITWISE_RSHIFT = 1078,      // CA_BITWISE_RSHIFT
    CA_LBRACKET = 1079,            // CA_LBRACKET
    CA_RBRACKET = 1080,            // CA_RBRACKET
    CA_RANGE = 1081,               // CA_RANGE
    CA_RANGE_INCLUSIVE = 1082,     // CA_RANGE_INCLUSIVE
    CA_DOT = 1083,                 // CA_DOT
    CA_INT_CONST = 1084,           // CA_INT_CONST
    CA_FLOAT_CONST = 1085,         // CA_FLOAT_CONST
    CA_CHAR_CONST = 1086,          // CA_CHAR_CONST
    CA_IDENTIFIER = 1087,          // CA_IDENTIFIER
    CA_NEG = 1088,                 // CA_NEG
    CA_POS = 1089                  // CA_POS
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 68, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_CA_ENTRY = 3,                          // CA_ENTRY
        S_CA_LET = 4,                            // CA_LET
        S_CA_MUT = 5,                            // CA_MUT
        S_CA_FN = 6,                             // CA_FN
        S_CA_RETURN = 7,                         // CA_RETURN
        S_CA_IF = 8,                             // CA_IF
        S_CA_ELSE = 9,                           // CA_ELSE
        S_CA_WHILE = 10,                         // CA_WHILE
        S_CA_FOR = 11,                           // CA_FOR
        S_CA_BREAK = 12,                         // CA_BREAK
        S_CA_CONTINUE = 13,                      // CA_CONTINUE
        S_CA_AS = 14,                            // CA_AS
        S_CA_RETURN_TYPE = 15,                   // CA_RETURN_TYPE
        S_CA_IN = 16,                            // CA_IN
        S_CA_CONST = 17,                         // CA_CONST
        S_CA_TRUE = 18,                          // CA_TRUE
        S_CA_FALSE = 19,                         // CA_FALSE
        S_CA_BOOL = 20,                          // CA_BOOL
        S_CA_INT32 = 21,                         // CA_INT32
        S_CA_FLOAT32 = 22,                       // CA_FLOAT32
        S_CA_CHAR = 23,                          // CA_CHAR
        S_CA_PLUS = 24,                          // CA_PLUS
        S_CA_MINUS = 25,                         // CA_MINUS
        S_CA_MUL = 26,                           // CA_MUL
        S_CA_DIV = 27,                           // CA_DIV
        S_CA_MOD = 28,                           // CA_MOD
        S_CA_AND = 29,                           // CA_AND
        S_CA_OR = 30,                            // CA_OR
        S_CA_NOT = 31,                           // CA_NOT
        S_CA_EQ = 32,                            // CA_EQ
        S_CA_NEQ = 33,                           // CA_NEQ
        S_CA_LT = 34,                            // CA_LT
        S_CA_GT = 35,                            // CA_GT
        S_CA_LTE = 36,                           // CA_LTE
        S_CA_GTE = 37,                           // CA_GTE
        S_CA_ASSIGN = 38,                        // CA_ASSIGN
        S_CA_COMMA = 39,                         // CA_COMMA
        S_CA_SEMICOLON = 40,                     // CA_SEMICOLON
        S_CA_LPAREN = 41,                        // CA_LPAREN
        S_CA_RPAREN = 42,                        // CA_RPAREN
        S_CA_LBRACE = 43,                        // CA_LBRACE
        S_CA_RBRACE = 44,                        // CA_RBRACE
        S_CA_COLON = 45,                         // CA_COLON
        S_CA_PLUS_ASSIGN = 46,                   // CA_PLUS_ASSIGN
        S_CA_MINUS_ASSIGN = 47,                  // CA_MINUS_ASSIGN
        S_CA_MUL_ASSIGN = 48,                    // CA_MUL_ASSIGN
        S_CA_DIV_ASSIGN = 49,                    // CA_DIV_ASSIGN
        S_CA_MOD_ASSIGN = 50,                    // CA_MOD_ASSIGN
        S_CA_BITWISE_AND = 51,                   // CA_BITWISE_AND
        S_CA_BITWISE_OR = 52,                    // CA_BITWISE_OR
        S_CA_BITWISE_XOR = 53,                   // CA_BITWISE_XOR
        S_CA_BITWISE_NOT = 54,                   // CA_BITWISE_NOT
        S_CA_BITWISE_LSHIFT = 55,                // CA_BITWISE_LSHIFT
        S_CA_BITWISE_RSHIFT = 56,                // CA_BITWISE_RSHIFT
        S_CA_LBRACKET = 57,                      // CA_LBRACKET
        S_CA_RBRACKET = 58,                      // CA_RBRACKET
        S_CA_RANGE = 59,                         // CA_RANGE
        S_CA_RANGE_INCLUSIVE = 60,               // CA_RANGE_INCLUSIVE
        S_CA_DOT = 61,                           // CA_DOT
        S_CA_INT_CONST = 62,                     // CA_INT_CONST
        S_CA_FLOAT_CONST = 63,                   // CA_FLOAT_CONST
        S_CA_CHAR_CONST = 64,                    // CA_CHAR_CONST
        S_CA_IDENTIFIER = 65,                    // CA_IDENTIFIER
        S_CA_NEG = 66,                           // CA_NEG
        S_CA_POS = 67,                           // CA_POS
        S_YYACCEPT = 68,                         // $accept
        S_program = 69,                          // program
        S_entry = 70,                            // entry
        S_statement_compound = 71,               // statement_compound
        S_statements = 72,                       // statements
        S_semicolon = 73,                        // semicolon
        S_opt_semicolon = 74,                    // opt_semicolon
        S_statement = 75,                        // statement
        S_type = 76,                             // type
        S_constant = 77,                         // constant
        S_array_type = 78,                       // array_type
        S_array_element = 79,                    // array_element
        S_array_expression = 80,                 // array_expression
        S_array_indices = 81,                    // array_indices
        S_array_access = 82,                     // array_access
        S_declaration = 83,                      // declaration
        S_expression = 84,                       // expression
        S_if = 85,                               // if
        S_else = 86,                             // else
        S_while = 87,                            // while
        S_for = 88,                              // for
        S_break = 89,                            // break
        S_continue = 90,                         // continue
        S_return = 91                            // return
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_CA_CHAR_CONST: // CA_CHAR_CONST
        value.move< char > (std::move (that.value));
        break;

      case symbol_kind::S_CA_FLOAT_CONST: // CA_FLOAT_CONST
        value.move< float > (std::move (that.value));
        break;

      case symbol_kind::S_CA_INT_CONST: // CA_INT_CONST
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_array_access: // array_access
        value.move< std::shared_ptr<ArrayAccessExpressionNode> > (std::move (that.value));
        break;

      case symbol_kind::S_array_expression: // array_expression
        value.move< std::shared_ptr<ArrayExpressionNode> > (std::move (that.value));
        break;

      case symbol_kind::S_array_type: // array_type
        value.move< std::shared_ptr<ArrayTypeNode> > (std::move (that.value));
        break;

      case symbol_kind::S_constant: // constant
        value.move< std::shared_ptr<ConstantExpressionNode> > (std::move (that.value));
        break;

      case symbol_kind::S_break: // break
      case symbol_kind::S_continue: // continue
        value.move< std::shared_ptr<ControlStatementNode> > (std::move (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< std::shared_ptr<DeclarationStatementNode> > (std::move (that.value));
        break;

      case symbol_kind::S_entry: // entry
        value.move< std::shared_ptr<EntryNode> > (std::move (that.value));
        break;

      case symbol_kind::S_expression: // expression
        value.move< std::shared_ptr<ExpressionNode> > (std::move (that.value));
        break;

      case symbol_kind::S_for: // for
        value.move< std::shared_ptr<ForStatementNode> > (std::move (that.value));
        break;

      case symbol_kind::S_if: // if
      case symbol_kind::S_else: // else
        value.move< std::shared_ptr<IfStatementNode> > (std::move (that.value));
        break;

      case symbol_kind::S_return: // return
        value.move< std::shared_ptr<ReturnStatementNode> > (std::move (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.move< std::shared_ptr<StatementNode> > (std::move (that.value));
        break;

      case symbol_kind::S_statement_compound: // statement_compound
      case symbol_kind::S_statements: // statements
        value.move< std::shared_ptr<StatementsNode> > (std::move (that.value));
        break;

      case symbol_kind::S_type: // type
        value.move< std::shared_ptr<TypeNode> > (std::move (that.value));
        break;

      case symbol_kind::S_while: // while
        value.move< std::shared_ptr<WhileStatementNode> > (std::move (that.value));
        break;

      case symbol_kind::S_CA_IDENTIFIER: // CA_IDENTIFIER
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_array_element: // array_element
      case symbol_kind::S_array_indices: // array_indices
        value.move< std::vector<std::shared_ptr<ExpressionNode>> > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, char&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const char& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, float&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const float& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<ArrayAccessExpressionNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<ArrayAccessExpressionNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<ArrayExpressionNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<ArrayExpressionNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<ArrayTypeNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<ArrayTypeNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<ConstantExpressionNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<ConstantExpressionNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<ControlStatementNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<ControlStatementNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<DeclarationStatementNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<DeclarationStatementNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<EntryNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<EntryNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<ExpressionNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<ExpressionNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<ForStatementNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<ForStatementNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<IfStatementNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<IfStatementNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<ReturnStatementNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<ReturnStatementNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<StatementNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<StatementNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<StatementsNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<StatementsNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<TypeNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<TypeNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<WhileStatementNode>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<WhileStatementNode>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::shared_ptr<ExpressionNode>>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<ExpressionNode>>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_CA_CHAR_CONST: // CA_CHAR_CONST
        value.template destroy< char > ();
        break;

      case symbol_kind::S_CA_FLOAT_CONST: // CA_FLOAT_CONST
        value.template destroy< float > ();
        break;

      case symbol_kind::S_CA_INT_CONST: // CA_INT_CONST
        value.template destroy< int > ();
        break;

      case symbol_kind::S_array_access: // array_access
        value.template destroy< std::shared_ptr<ArrayAccessExpressionNode> > ();
        break;

      case symbol_kind::S_array_expression: // array_expression
        value.template destroy< std::shared_ptr<ArrayExpressionNode> > ();
        break;

      case symbol_kind::S_array_type: // array_type
        value.template destroy< std::shared_ptr<ArrayTypeNode> > ();
        break;

      case symbol_kind::S_constant: // constant
        value.template destroy< std::shared_ptr<ConstantExpressionNode> > ();
        break;

      case symbol_kind::S_break: // break
      case symbol_kind::S_continue: // continue
        value.template destroy< std::shared_ptr<ControlStatementNode> > ();
        break;

      case symbol_kind::S_declaration: // declaration
        value.template destroy< std::shared_ptr<DeclarationStatementNode> > ();
        break;

      case symbol_kind::S_entry: // entry
        value.template destroy< std::shared_ptr<EntryNode> > ();
        break;

      case symbol_kind::S_expression: // expression
        value.template destroy< std::shared_ptr<ExpressionNode> > ();
        break;

      case symbol_kind::S_for: // for
        value.template destroy< std::shared_ptr<ForStatementNode> > ();
        break;

      case symbol_kind::S_if: // if
      case symbol_kind::S_else: // else
        value.template destroy< std::shared_ptr<IfStatementNode> > ();
        break;

      case symbol_kind::S_return: // return
        value.template destroy< std::shared_ptr<ReturnStatementNode> > ();
        break;

      case symbol_kind::S_statement: // statement
        value.template destroy< std::shared_ptr<StatementNode> > ();
        break;

      case symbol_kind::S_statement_compound: // statement_compound
      case symbol_kind::S_statements: // statements
        value.template destroy< std::shared_ptr<StatementsNode> > ();
        break;

      case symbol_kind::S_type: // type
        value.template destroy< std::shared_ptr<TypeNode> > ();
        break;

      case symbol_kind::S_while: // while
        value.template destroy< std::shared_ptr<WhileStatementNode> > ();
        break;

      case symbol_kind::S_CA_IDENTIFIER: // CA_IDENTIFIER
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_array_element: // array_element
      case symbol_kind::S_array_indices: // array_indices
        value.template destroy< std::vector<std::shared_ptr<ExpressionNode>> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return CarlosParser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::YYEOF
                   || tok == token::YYerror
                   || tok == token::YYUNDEF
                   || tok == token::CA_ENTRY
                   || (token::CA_LET <= tok && tok <= token::CA_DOT)
                   || (token::CA_NEG <= tok && tok <= token::CA_POS));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, char v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const char& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::CA_CHAR_CONST);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, float v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const float& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::CA_FLOAT_CONST);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::CA_INT_CONST);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::CA_IDENTIFIER);
#endif
      }
    };

    /// Build a parser object.
    CarlosParser (CarlosLexer &lexer_yyarg);
    virtual ~CarlosParser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    CarlosParser (const CarlosParser&) = delete;
    /// Non copyable.
    CarlosParser& operator= (const CarlosParser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF (location_type l)
      {
        return symbol_type (token::YYEOF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYEOF (const location_type& l)
      {
        return symbol_type (token::YYEOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_ENTRY (location_type l)
      {
        return symbol_type (token::CA_ENTRY, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_ENTRY (const location_type& l)
      {
        return symbol_type (token::CA_ENTRY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_LET (location_type l)
      {
        return symbol_type (token::CA_LET, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_LET (const location_type& l)
      {
        return symbol_type (token::CA_LET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_MUT (location_type l)
      {
        return symbol_type (token::CA_MUT, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_MUT (const location_type& l)
      {
        return symbol_type (token::CA_MUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_FN (location_type l)
      {
        return symbol_type (token::CA_FN, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_FN (const location_type& l)
      {
        return symbol_type (token::CA_FN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_RETURN (location_type l)
      {
        return symbol_type (token::CA_RETURN, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_RETURN (const location_type& l)
      {
        return symbol_type (token::CA_RETURN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_IF (location_type l)
      {
        return symbol_type (token::CA_IF, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_IF (const location_type& l)
      {
        return symbol_type (token::CA_IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_ELSE (location_type l)
      {
        return symbol_type (token::CA_ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_ELSE (const location_type& l)
      {
        return symbol_type (token::CA_ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_WHILE (location_type l)
      {
        return symbol_type (token::CA_WHILE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_WHILE (const location_type& l)
      {
        return symbol_type (token::CA_WHILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_FOR (location_type l)
      {
        return symbol_type (token::CA_FOR, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_FOR (const location_type& l)
      {
        return symbol_type (token::CA_FOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_BREAK (location_type l)
      {
        return symbol_type (token::CA_BREAK, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_BREAK (const location_type& l)
      {
        return symbol_type (token::CA_BREAK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_CONTINUE (location_type l)
      {
        return symbol_type (token::CA_CONTINUE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_CONTINUE (const location_type& l)
      {
        return symbol_type (token::CA_CONTINUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_AS (location_type l)
      {
        return symbol_type (token::CA_AS, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_AS (const location_type& l)
      {
        return symbol_type (token::CA_AS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_RETURN_TYPE (location_type l)
      {
        return symbol_type (token::CA_RETURN_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_RETURN_TYPE (const location_type& l)
      {
        return symbol_type (token::CA_RETURN_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_IN (location_type l)
      {
        return symbol_type (token::CA_IN, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_IN (const location_type& l)
      {
        return symbol_type (token::CA_IN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_CONST (location_type l)
      {
        return symbol_type (token::CA_CONST, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_CONST (const location_type& l)
      {
        return symbol_type (token::CA_CONST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_TRUE (location_type l)
      {
        return symbol_type (token::CA_TRUE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_TRUE (const location_type& l)
      {
        return symbol_type (token::CA_TRUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_FALSE (location_type l)
      {
        return symbol_type (token::CA_FALSE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_FALSE (const location_type& l)
      {
        return symbol_type (token::CA_FALSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_BOOL (location_type l)
      {
        return symbol_type (token::CA_BOOL, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_BOOL (const location_type& l)
      {
        return symbol_type (token::CA_BOOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_INT32 (location_type l)
      {
        return symbol_type (token::CA_INT32, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_INT32 (const location_type& l)
      {
        return symbol_type (token::CA_INT32, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_FLOAT32 (location_type l)
      {
        return symbol_type (token::CA_FLOAT32, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_FLOAT32 (const location_type& l)
      {
        return symbol_type (token::CA_FLOAT32, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_CHAR (location_type l)
      {
        return symbol_type (token::CA_CHAR, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_CHAR (const location_type& l)
      {
        return symbol_type (token::CA_CHAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_PLUS (location_type l)
      {
        return symbol_type (token::CA_PLUS, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_PLUS (const location_type& l)
      {
        return symbol_type (token::CA_PLUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_MINUS (location_type l)
      {
        return symbol_type (token::CA_MINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_MINUS (const location_type& l)
      {
        return symbol_type (token::CA_MINUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_MUL (location_type l)
      {
        return symbol_type (token::CA_MUL, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_MUL (const location_type& l)
      {
        return symbol_type (token::CA_MUL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_DIV (location_type l)
      {
        return symbol_type (token::CA_DIV, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_DIV (const location_type& l)
      {
        return symbol_type (token::CA_DIV, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_MOD (location_type l)
      {
        return symbol_type (token::CA_MOD, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_MOD (const location_type& l)
      {
        return symbol_type (token::CA_MOD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_AND (location_type l)
      {
        return symbol_type (token::CA_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_AND (const location_type& l)
      {
        return symbol_type (token::CA_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_OR (location_type l)
      {
        return symbol_type (token::CA_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_OR (const location_type& l)
      {
        return symbol_type (token::CA_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_NOT (location_type l)
      {
        return symbol_type (token::CA_NOT, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_NOT (const location_type& l)
      {
        return symbol_type (token::CA_NOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_EQ (location_type l)
      {
        return symbol_type (token::CA_EQ, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_EQ (const location_type& l)
      {
        return symbol_type (token::CA_EQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_NEQ (location_type l)
      {
        return symbol_type (token::CA_NEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_NEQ (const location_type& l)
      {
        return symbol_type (token::CA_NEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_LT (location_type l)
      {
        return symbol_type (token::CA_LT, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_LT (const location_type& l)
      {
        return symbol_type (token::CA_LT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_GT (location_type l)
      {
        return symbol_type (token::CA_GT, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_GT (const location_type& l)
      {
        return symbol_type (token::CA_GT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_LTE (location_type l)
      {
        return symbol_type (token::CA_LTE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_LTE (const location_type& l)
      {
        return symbol_type (token::CA_LTE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_GTE (location_type l)
      {
        return symbol_type (token::CA_GTE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_GTE (const location_type& l)
      {
        return symbol_type (token::CA_GTE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_ASSIGN (location_type l)
      {
        return symbol_type (token::CA_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_ASSIGN (const location_type& l)
      {
        return symbol_type (token::CA_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_COMMA (location_type l)
      {
        return symbol_type (token::CA_COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_COMMA (const location_type& l)
      {
        return symbol_type (token::CA_COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_SEMICOLON (location_type l)
      {
        return symbol_type (token::CA_SEMICOLON, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_SEMICOLON (const location_type& l)
      {
        return symbol_type (token::CA_SEMICOLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_LPAREN (location_type l)
      {
        return symbol_type (token::CA_LPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_LPAREN (const location_type& l)
      {
        return symbol_type (token::CA_LPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_RPAREN (location_type l)
      {
        return symbol_type (token::CA_RPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_RPAREN (const location_type& l)
      {
        return symbol_type (token::CA_RPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_LBRACE (location_type l)
      {
        return symbol_type (token::CA_LBRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_LBRACE (const location_type& l)
      {
        return symbol_type (token::CA_LBRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_RBRACE (location_type l)
      {
        return symbol_type (token::CA_RBRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_RBRACE (const location_type& l)
      {
        return symbol_type (token::CA_RBRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_COLON (location_type l)
      {
        return symbol_type (token::CA_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_COLON (const location_type& l)
      {
        return symbol_type (token::CA_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_PLUS_ASSIGN (location_type l)
      {
        return symbol_type (token::CA_PLUS_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_PLUS_ASSIGN (const location_type& l)
      {
        return symbol_type (token::CA_PLUS_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_MINUS_ASSIGN (location_type l)
      {
        return symbol_type (token::CA_MINUS_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_MINUS_ASSIGN (const location_type& l)
      {
        return symbol_type (token::CA_MINUS_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_MUL_ASSIGN (location_type l)
      {
        return symbol_type (token::CA_MUL_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_MUL_ASSIGN (const location_type& l)
      {
        return symbol_type (token::CA_MUL_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_DIV_ASSIGN (location_type l)
      {
        return symbol_type (token::CA_DIV_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_DIV_ASSIGN (const location_type& l)
      {
        return symbol_type (token::CA_DIV_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_MOD_ASSIGN (location_type l)
      {
        return symbol_type (token::CA_MOD_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_MOD_ASSIGN (const location_type& l)
      {
        return symbol_type (token::CA_MOD_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_BITWISE_AND (location_type l)
      {
        return symbol_type (token::CA_BITWISE_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_BITWISE_AND (const location_type& l)
      {
        return symbol_type (token::CA_BITWISE_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_BITWISE_OR (location_type l)
      {
        return symbol_type (token::CA_BITWISE_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_BITWISE_OR (const location_type& l)
      {
        return symbol_type (token::CA_BITWISE_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_BITWISE_XOR (location_type l)
      {
        return symbol_type (token::CA_BITWISE_XOR, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_BITWISE_XOR (const location_type& l)
      {
        return symbol_type (token::CA_BITWISE_XOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_BITWISE_NOT (location_type l)
      {
        return symbol_type (token::CA_BITWISE_NOT, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_BITWISE_NOT (const location_type& l)
      {
        return symbol_type (token::CA_BITWISE_NOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_BITWISE_LSHIFT (location_type l)
      {
        return symbol_type (token::CA_BITWISE_LSHIFT, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_BITWISE_LSHIFT (const location_type& l)
      {
        return symbol_type (token::CA_BITWISE_LSHIFT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_BITWISE_RSHIFT (location_type l)
      {
        return symbol_type (token::CA_BITWISE_RSHIFT, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_BITWISE_RSHIFT (const location_type& l)
      {
        return symbol_type (token::CA_BITWISE_RSHIFT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_LBRACKET (location_type l)
      {
        return symbol_type (token::CA_LBRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_LBRACKET (const location_type& l)
      {
        return symbol_type (token::CA_LBRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_RBRACKET (location_type l)
      {
        return symbol_type (token::CA_RBRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_RBRACKET (const location_type& l)
      {
        return symbol_type (token::CA_RBRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_RANGE (location_type l)
      {
        return symbol_type (token::CA_RANGE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_RANGE (const location_type& l)
      {
        return symbol_type (token::CA_RANGE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_RANGE_INCLUSIVE (location_type l)
      {
        return symbol_type (token::CA_RANGE_INCLUSIVE, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_RANGE_INCLUSIVE (const location_type& l)
      {
        return symbol_type (token::CA_RANGE_INCLUSIVE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_DOT (location_type l)
      {
        return symbol_type (token::CA_DOT, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_DOT (const location_type& l)
      {
        return symbol_type (token::CA_DOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_INT_CONST (int v, location_type l)
      {
        return symbol_type (token::CA_INT_CONST, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CA_INT_CONST (const int& v, const location_type& l)
      {
        return symbol_type (token::CA_INT_CONST, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_FLOAT_CONST (float v, location_type l)
      {
        return symbol_type (token::CA_FLOAT_CONST, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CA_FLOAT_CONST (const float& v, const location_type& l)
      {
        return symbol_type (token::CA_FLOAT_CONST, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_CHAR_CONST (char v, location_type l)
      {
        return symbol_type (token::CA_CHAR_CONST, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CA_CHAR_CONST (const char& v, const location_type& l)
      {
        return symbol_type (token::CA_CHAR_CONST, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_IDENTIFIER (std::string v, location_type l)
      {
        return symbol_type (token::CA_IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CA_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::CA_IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_NEG (location_type l)
      {
        return symbol_type (token::CA_NEG, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_NEG (const location_type& l)
      {
        return symbol_type (token::CA_NEG, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CA_POS (location_type l)
      {
        return symbol_type (token::CA_POS, std::move (l));
      }
#else
      static
      symbol_type
      make_CA_POS (const location_type& l)
      {
        return symbol_type (token::CA_POS, l);
      }
#endif


    class context
    {
    public:
      context (const CarlosParser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const CarlosParser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    CarlosParser (const CarlosParser&);
    /// Non copyable.
    CarlosParser& operator= (const CarlosParser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const unsigned char yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const unsigned char yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 560,     ///< Last index in yytable_.
      yynnts_ = 24,  ///< Number of nonterminal symbols.
      yyfinal_ = 6 ///< Termination state number.
    };


    // User arguments.
    CarlosLexer &lexer;

  };

  inline
  CarlosParser::symbol_kind_type
  CarlosParser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     2,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67
    };
    // Last valid token kind.
    const int code_max = 1089;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  CarlosParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_CA_CHAR_CONST: // CA_CHAR_CONST
        value.copy< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CA_FLOAT_CONST: // CA_FLOAT_CONST
        value.copy< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CA_INT_CONST: // CA_INT_CONST
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_access: // array_access
        value.copy< std::shared_ptr<ArrayAccessExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_expression: // array_expression
        value.copy< std::shared_ptr<ArrayExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_type: // array_type
        value.copy< std::shared_ptr<ArrayTypeNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constant: // constant
        value.copy< std::shared_ptr<ConstantExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_break: // break
      case symbol_kind::S_continue: // continue
        value.copy< std::shared_ptr<ControlStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< std::shared_ptr<DeclarationStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_entry: // entry
        value.copy< std::shared_ptr<EntryNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
        value.copy< std::shared_ptr<ExpressionNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for: // for
        value.copy< std::shared_ptr<ForStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if: // if
      case symbol_kind::S_else: // else
        value.copy< std::shared_ptr<IfStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_return: // return
        value.copy< std::shared_ptr<ReturnStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.copy< std::shared_ptr<StatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_compound: // statement_compound
      case symbol_kind::S_statements: // statements
        value.copy< std::shared_ptr<StatementsNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.copy< std::shared_ptr<TypeNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while: // while
        value.copy< std::shared_ptr<WhileStatementNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CA_IDENTIFIER: // CA_IDENTIFIER
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_element: // array_element
      case symbol_kind::S_array_indices: // array_indices
        value.copy< std::vector<std::shared_ptr<ExpressionNode>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  CarlosParser::symbol_kind_type
  CarlosParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  CarlosParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  CarlosParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_CA_CHAR_CONST: // CA_CHAR_CONST
        value.move< char > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CA_FLOAT_CONST: // CA_FLOAT_CONST
        value.move< float > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CA_INT_CONST: // CA_INT_CONST
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_array_access: // array_access
        value.move< std::shared_ptr<ArrayAccessExpressionNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_array_expression: // array_expression
        value.move< std::shared_ptr<ArrayExpressionNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_array_type: // array_type
        value.move< std::shared_ptr<ArrayTypeNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_constant: // constant
        value.move< std::shared_ptr<ConstantExpressionNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_break: // break
      case symbol_kind::S_continue: // continue
        value.move< std::shared_ptr<ControlStatementNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< std::shared_ptr<DeclarationStatementNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_entry: // entry
        value.move< std::shared_ptr<EntryNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expression: // expression
        value.move< std::shared_ptr<ExpressionNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_for: // for
        value.move< std::shared_ptr<ForStatementNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_if: // if
      case symbol_kind::S_else: // else
        value.move< std::shared_ptr<IfStatementNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_return: // return
        value.move< std::shared_ptr<ReturnStatementNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement: // statement
        value.move< std::shared_ptr<StatementNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement_compound: // statement_compound
      case symbol_kind::S_statements: // statements
        value.move< std::shared_ptr<StatementsNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type: // type
        value.move< std::shared_ptr<TypeNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_while: // while
        value.move< std::shared_ptr<WhileStatementNode> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CA_IDENTIFIER: // CA_IDENTIFIER
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_array_element: // array_element
      case symbol_kind::S_array_indices: // array_indices
        value.move< std::vector<std::shared_ptr<ExpressionNode>> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  CarlosParser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  CarlosParser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  CarlosParser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  CarlosParser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  CarlosParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  CarlosParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  CarlosParser::symbol_kind_type
  CarlosParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  CarlosParser::symbol_kind_type
  CarlosParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 17 "carlos.ypp"
} // carlos
#line 3209 "carlos.parser.h"




#endif // !YY_YY_CARLOS_PARSER_H_INCLUDED