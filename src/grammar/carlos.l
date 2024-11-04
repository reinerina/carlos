%option c++
%option outfile="carlos.lex.cpp"
%option noyywrap
%option yylineno
%option yyclass="CarlosLexer"
%option prefix="Carlos"

%{
#include <iostream>
#include "carlos.lex.h"
#include "carlos.parser.h"
using namespace carlos;
using Token = CarlosParser::token;
%}

%x IN_COMMENT

ENTRYPOINT (fn[ ]+main[ ]*\([ ]*\)[ ]*)
INTEGER ([+-]?0x[0-9a-fA-F]+)|([+-]?0b[01]+)|([+-]?[0-9]+)
FLOAT ([+-]?[0-9]+\.[0-9]+([eE][+-]?[0-9]+)?)
CHAR (\'.\')
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
OPERATOR ([+*-/%=,;!<>(){}:\.\[\]])
COMMENT (\/\/[^\n]*)
BEGIN_COMMENT (\/\*)
END_COMMENT (\*\/)
WS ([ \t\r\a]+)
EOL (\n)

%%

{ENTRYPOINT} {
  location.next_word(yyleng);
  return CarlosParser::make_CA_ENTRY(location);
}

{WS} {
  location.next_word(yyleng);
  // Ignore whitespace
}

{EOL} {
  location.next_line(yylineno);
  // Ignore newlines
}

{COMMENT} {
  location.next_word(yyleng);
  // Ignore comments
}

{BEGIN_COMMENT} {
  location.next_word(yyleng);
  BEGIN(IN_COMMENT);
}

<IN_COMMENT>{
  location.next_word(yyleng);
  {END_COMMENT} {
    BEGIN(INITIAL);
  }
  [^*]+ {
    // Ignore comments
  }
}

{OPERATOR} {
  location.next_word(yyleng);
  switch (yytext[0]) {
    case '+': return CarlosParser::make_CA_PLUS(location);
    case '-': return CarlosParser::make_CA_MINUS(location);
    case '*': return CarlosParser::make_CA_MUL(location);
    case '/': return CarlosParser::make_CA_DIV(location);
    case '%': return CarlosParser::make_CA_MOD(location);
    case '&': return CarlosParser::make_CA_BITWISE_AND(location);
    case '|': return CarlosParser::make_CA_BITWISE_OR(location);
    case '!': return CarlosParser::make_CA_NOT(location);
    case '=': return CarlosParser::make_CA_ASSIGN(location);
    case ',': return CarlosParser::make_CA_COMMA(location);
    case ';': return CarlosParser::make_CA_SEMICOLON(location);
    case '<': return CarlosParser::make_CA_LT(location);
    case '>': return CarlosParser::make_CA_GT(location);
    case '(': return CarlosParser::make_CA_LPAREN(location);
    case ')': return CarlosParser::make_CA_RPAREN(location);
    case '{': return CarlosParser::make_CA_LBRACE(location);
    case '}': return CarlosParser::make_CA_RBRACE(location);
    case '.': return CarlosParser::make_CA_DOT(location);
    case ':': return CarlosParser::make_CA_COLON(location);
    case '[': return CarlosParser::make_CA_LBRACKET(location);
    case ']': return CarlosParser::make_CA_RBRACKET(location);
  }
}

"let" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_LET(location);
}

"mut" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_MUT(location);
}

"as" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_AS(location);
}

"bool" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_BOOL(location);
}

"i32" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_INT32(location);
}

"f32" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_FLOAT32(location);
}

"char" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_CHAR(location);
}

"fn" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_FN(location);
}

"return" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_RETURN(location);
}

"const" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_CONST(location);
}

"if" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_IF(location);
}

"else" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_ELSE(location);
}

"while" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_WHILE(location);
}

"for" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_FOR(location);
}

"break" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_BREAK(location);
}

"continue" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_CONTINUE(location);
}

"in" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_IN(location);
}

"true" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_TRUE(location);
}

"false" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_FALSE(location);
}

"->" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_RETURN_TYPE(location);
}

">=" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_GTE(location);
}

"<=" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_LTE(location);
}

"==" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_EQ(location);
}

"!=" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_NEQ(location);
}

"||" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_OR(location);
}

"&&" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_AND(location);
}

".." {
  location.next_word(yyleng);
  return CarlosParser::make_CA_RANGE(location);
}

"..=" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_RANGE_INCLUSIVE(location);
}

"+=" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_PLUS_ASSIGN(location);
}

"-=" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_MINUS_ASSIGN(location);
}

"*=" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_MUL_ASSIGN(location);
}

"/=" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_DIV_ASSIGN(location);
}

"%=" {
  location.next_word(yyleng);
  return CarlosParser::make_CA_MOD_ASSIGN(location);
}

{INTEGER} {
  location.next_word(yyleng);
  if (yytext[0] == '0') {
    if (yytext[1] == 'x') {
      return CarlosParser::make_CA_INT_CONST(std::strtol(yytext, nullptr, 16), location);
    } else if (yytext[1] == 'b') {
      return CarlosParser::make_CA_INT_CONST(std::strtol(yytext, nullptr, 2), location);
    }
  }
  return CarlosParser::make_CA_INT_CONST(std::strtol(yytext, nullptr, 10), location);
}

{FLOAT} {
  location.next_word(yyleng);
  return CarlosParser::make_CA_FLOAT_CONST(std::strtof(yytext, nullptr), location);
}

{CHAR} {
  location.next_word(yyleng);
  return CarlosParser::make_CA_CHAR_CONST(yytext[1], location);
}

{IDENTIFIER} {
  location.next_word(yyleng);
  return CarlosParser::make_CA_IDENTIFIER(yytext, location);
}

<IN_COMMENT><<EOF>> {
  std::cerr << "Error: Unterminated comment" << std::endl;
  exit(1);
}

<<EOF>> {
  return CarlosParser::make_YYEOF(location);
}

. {
  location.next_word(yyleng);
  std::cerr << "Error at " << location << ": Unexpected character '" << yytext[0] << "'" << std::endl;
  return CarlosParser::make_YYerror(location);
}

%%