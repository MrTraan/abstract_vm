#include "Tokenizer.hpp"

static bool isWhiteChar(char c) {
  if (c == ' ' || c == '\t') {
    return true;
  }
  return false;
}

static bool isIdentChar(char c) {
  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
      (c >= '0' && c <= '9')) {
    return true;
  }
  return false;
}

bool Tokenizer::peekFloatingNumber() {
  int i = _reader;
  bool floatingPoint = false;

  if (_input[i] == '-')
    i++;

  while (_input[i]) {
    if (_input[i] == ')') {
      if (i == 0 || i == _reader || _input[i - 1] == '.' ||
          _input[i - 1] == '-') {
        return false;
      }
      return floatingPoint;
    }
    if (_input[i] == '.') {
      if (i == _reader || floatingPoint == true) {
        return false;
      }
      floatingPoint = true;
    } else if (_input[i] > '9' || _input[i] < '0') {
      return false;
    }
    i++;
  }
  return false;
}

bool Tokenizer::peekFixedNumber() {
  int i = _reader;

  if (_input[i] == '-')
    i++;

  while (_input[i]) {
    if (_input[i] == ')') {
      if (i == 0 || i == _reader || _input[i - 1] == '-') {
        return false;
      }
      return true;
    }
    if (_input[i] > '9' || _input[i] < '0') {
      return false;
    }
    i++;
  }
  return false;
}

Token Tokenizer::readFloatingNumber() {
  std::string s = "";

  while (peekChar() == '.' || peekChar() == '-' ||
         (peekChar() >= '0' && peekChar() <= '9')) {
    s += readChar();
  }
  Token ret = {T_FLOATING_NUMBER, s};
  return ret;
}

Token Tokenizer::readFixedNumber() {
  std::string s = "";

  while (peekChar() == '-' || (peekChar() >= '0' && peekChar() <= '9')) {
    s += readChar();
  }
  Token ret = {T_FIXED_NUMBER, s};
  return ret;
}

Tokenizer::Tokenizer(std::string input) : _input(input), _reader(0) {}

Tokenizer::Tokenizer(const Tokenizer& src) {
  *this = src;
}

Tokenizer::~Tokenizer(void) {}

Tokenizer& Tokenizer::operator=(const Tokenizer& rhs) {
  this->_input = rhs._input;
  this->_reader = rhs._reader;
  return *this;
}

Token Tokenizer::nextToken() {
  skipWhitespace();

  if (peekChar() == 0) {
    Token ret = {T_EOF, ""};
    return ret;
  }
  if (peekChar() == '\n') {
    readChar();
    Token ret = {T_EOL, "\n"};
    return ret;
  }
  if (peekChar() == ';') {
    readChar();
    if (peekChar() == ';') {
      Token ret = {T_EOF, ";;"};
      return ret;
    }
    skipComment();
    Token ret = {T_COMMENT, ""};
    return ret;
  }
  if (peekChar() == '(') {
    readChar();
    Token ret = {T_L_PAREN, "("};
    return ret;
  }
  if (peekChar() == ')') {
    readChar();
    Token ret = {T_R_PAREN, ")"};
    return ret;
  }
  if (peekFloatingNumber()) {
    return readFloatingNumber();
  }
  if (peekFixedNumber()) {
    return readFixedNumber();
  }
  return readIdentifer();
}

Token Tokenizer::readIdentifer() {
  std::string ident = "";

  while (isIdentChar(peekChar()))
    ident += readChar();

  if (ident == "add") {
    Token ret = {T_ADD, ident};
    return ret;
  }
  if (ident == "sub") {
    Token ret = {T_SUB, ident};
    return ret;
  }
  if (ident == "mul") {
    Token ret = {T_MUL, ident};
    return ret;
  }
  if (ident == "div") {
    Token ret = {T_DIV, ident};
    return ret;
  }
  if (ident == "mod") {
    Token ret = {T_MOD, ident};
    return ret;
  }
  if (ident == "push") {
    Token ret = {T_PUSH, ident};
    return ret;
  }
  if (ident == "pop") {
    Token ret = {T_POP, ident};
    return ret;
  }
  if (ident == "dump") {
    Token ret = {T_DUMP, ident};
    return ret;
  }
  if (ident == "exit") {
    Token ret = {T_EXIT, ident};
    return ret;
  }
  if (ident == "assert") {
    Token ret = {T_ASSERT, ident};
    return ret;
  }
  if (ident == "int8") {
    Token ret = {T_INT_8, ident};
    return ret;
  }
  if (ident == "int16") {
    Token ret = {T_INT_16, ident};
    return ret;
  }
  if (ident == "int32") {
    Token ret = {T_INT_32, ident};
    return ret;
  }
  if (ident == "float") {
    Token ret = {T_FLOAT, ident};
    return ret;
  }
  if (ident == "double") {
    Token ret = {T_DOUBLE, ident};
    return ret;
  }

  Token ret = {T_INVALID, ident};
  return ret;
}

void Tokenizer::skipWhitespace() {
  while (isWhiteChar(peekChar()))
    readChar();
}

char Tokenizer::peekChar() {
  if ((size_t)_reader > _input.size())
    return 0;
  return _input[_reader];
}

char Tokenizer::readChar() {
  if ((size_t)_reader > _input.size())
    return 0;
  char res = _input[_reader];
  _reader++;
  return res;
}

void Tokenizer::skipComment() {
  char currentChar = 0;
  do {
    currentChar = readChar();
  } while (currentChar && currentChar != '\n');
}

void debugPrintToken(const Token& token) {
  if (token.type == T_ADD) {
    std::cout << "T_ADD : " << token.value << "\n";
  }
  if (token.type == T_SUB) {
    std::cout << "T_SUB : " << token.value << "\n";
  }
  if (token.type == T_MUL) {
    std::cout << "T_MUL : " << token.value << "\n";
  }
  if (token.type == T_DIV) {
    std::cout << "T_DIV : " << token.value << "\n";
  }
  if (token.type == T_MOD) {
    std::cout << "T_MOD : " << token.value << "\n";
  }
  if (token.type == T_PUSH) {
    std::cout << "T_PUSH : " << token.value << "\n";
  }
  if (token.type == T_POP) {
    std::cout << "T_POP : " << token.value << "\n";
  }
  if (token.type == T_DUMP) {
    std::cout << "T_DUMP : " << token.value << "\n";
  }
  if (token.type == T_EXIT) {
    std::cout << "T_EXIT : " << token.value << "\n";
  }
  if (token.type == T_ASSERT) {
    std::cout << "T_ASSERT : " << token.value << "\n";
  }
  if (token.type == T_INT_8) {
    std::cout << "T_INT_8 : " << token.value << "\n";
  }
  if (token.type == T_INT_16) {
    std::cout << "T_INT_16 : " << token.value << "\n";
  }
  if (token.type == T_INT_32) {
    std::cout << "T_INT_32 : " << token.value << "\n";
  }
  if (token.type == T_FLOAT) {
    std::cout << "T_FLOAT : " << token.value << "\n";
  }
  if (token.type == T_DOUBLE) {
    std::cout << "T_DOUBLE : " << token.value << "\n";
  }
  if (token.type == T_R_PAREN) {
    std::cout << "T_R_PAREN : " << token.value << "\n";
  }
  if (token.type == T_L_PAREN) {
    std::cout << "T_L_PAREN : " << token.value << "\n";
  }
  if (token.type == T_EOF) {
    std::cout << "T_EOF : " << token.value << "\n";
  }
  if (token.type == T_EOL) {
    std::cout << "T_EOL : " << token.value << "\n";
  }
  if (token.type == T_FIXED_NUMBER) {
    std::cout << "T_FIXED_NUMBER : " << token.value << "\n";
  }
  if (token.type == T_FLOATING_NUMBER) {
    std::cout << "T_FLOATING_NUMBER : " << token.value << "\n";
  }
  if (token.type == T_INVALID) {
    std::cout << "T_INVALID : " << token.value << "\n";
  }
}
