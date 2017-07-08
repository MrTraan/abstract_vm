#include <iostream>
#include <IOperand.hpp>
#include <OperandFactory.hpp>
#include <Tokenizer.hpp>
#include <Parser.hpp>

#include <iostream>
#include <fstream>

std::string readFile(char* path) {
  std::string line;
  std::string total = "";
  std::ifstream myfile(path);

  if (myfile.is_open()) {
    while (std::getline(myfile, line)) {
      total += line;
      total += "\n";
    }
    myfile.close();
    return total;
  }

  else
    std::cout << "Unable to open file";

  return "";
}

int main(int ac, char** av) {
  /* std::string const tab[2] = {"3.67", "-1.3"}; */
  /* OperandFactory factory; */
  /* IOperand const* a = factory.createOperand(FLOAT, tab[0]); */
  /* IOperand const* b = factory.createOperand(FLOAT, tab[1]); */

  /* IOperand const* plus = *a + *b; */
  /* IOperand const* minus = *a - *b; */
  /* IOperand const* times = *a * *b; */
  /* IOperand const* divide = *a / *b; */

  /* std::cout << "3.67 + -1.3: " << plus->toString() << "\n"; */
  /* std::cout << "3.67 - -1.3: " << minus->toString() << "\n"; */
  /* std::cout << "3.67 * -1.3: " << times->toString() << "\n"; */
  /* std::cout << "3.67 / -1.3: " << divide->toString() << "\n"; */

  /* delete plus; */
  /* delete minus; */
  /* delete times; */
  /* delete divide; */

  if (ac <= 1)
    return (1);

  std::string data = readFile(av[1]);

  std::cout << data;

  Tokenizer tokenizer(data.c_str());
  Parser parser;
  Token curTok;

  do {
    curTok = tokenizer.nextToken();
    parser.pushToken(curTok);
  } while (curTok.type != T_EOF && curTok.type != T_INVALID);

  parser.debugPrintTokenList();

  return (0);
}
