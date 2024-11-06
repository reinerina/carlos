//
// Created by 陈洋 on 24-10-16.
//

#ifndef CARLOS_LEX_H
#define CARLOS_LEX_H
#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer CarlosFlexLexer
#include <FlexLexer.h>
#endif

#include "carlos.parser.h"

#undef YY_DECL
#define YY_DECL carlos::CarlosParser::symbol_type carlos::CarlosLexer::lex()

namespace carlos {

class CarlosLexer final : public CarlosFlexLexer {
 public:
  CarlosLexer() = default;
  explicit CarlosLexer(std::istream& in, const bool display)
      : CarlosFlexLexer(&in), display(display) {}

  CarlosParser::symbol_type lex();

  Location location{1, 1};
  bool display{};
};
};  // namespace carlos

#endif  // CARLOS_LEX_H
