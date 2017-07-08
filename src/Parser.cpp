#include <Parser.hpp>

Parser::Parser(void) {}

Parser::Parser(const Parser& src) {
  *this = src;
}

Parser::~Parser(void) {}

Parser& Parser::operator=(const Parser& rhs) {
  _tokens = rhs._tokens;
  return *this;
}

void Parser::pushToken(Token token) {
  _tokens.push_back(token);
}

void Parser::debugPrintTokenList() {
  for (std::list<Token>::iterator it = _tokens.begin(); it != _tokens.end();
       it++) {
    debugPrintToken(*it);
  }
}
