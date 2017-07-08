#pragma once

#include <iostream>

enum eToken {
  T_ADD,
  T_SUB,
  T_MUL,
  T_DIV,
  T_MOD,

  T_PUSH,
  T_POP,
  T_DUMP,
  T_EXIT,
  T_ASSERT,

  T_INT_8,
  T_INT_16,
  T_INT_32,
  T_FLOAT,
  T_DOUBLE,

  T_R_PAREN,
  T_L_PAREN,

  T_EOF,
  T_EOL,
  T_COMMENT,
  T_FIXED_NUMBER,
  T_FLOATING_NUMBER,
  T_INVALID
};

struct Token {
  eToken type;
  std::string value;
};

class Tokenizer {
 public:
  Tokenizer(std::string input);
  Tokenizer(const Tokenizer& src);
  ~Tokenizer(void);

  Tokenizer& operator=(const Tokenizer& rhs);

  Token nextToken();

 private:
  std::string _input;
  int _reader;

  void skipWhitespace();
  void skipComment();
  char peekChar();
  char readChar();
  bool peekFloatingNumber();
  bool peekFixedNumber();
  Token readFloatingNumber();
  Token readFixedNumber();
  Token readIdentifer();
};

void debugPrintToken(const Token& token);
