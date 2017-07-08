#pragma once

#include <Tokenizer.hpp>
#include <list>

class Parser {
 public:
  Parser(void);
  Parser(const Parser& src);
  ~Parser(void);

  Parser& operator=(const Parser& rhs);

  void pushToken(Token token);

  void debugPrintTokenList();

 private:
  std::list<Token> _tokens;
};
