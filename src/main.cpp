#include <iostream>
#include <IOperand.hpp>
#include <OperandFactory.hpp>
#include <Tokenizer.hpp>

#include <iostream>
#include <fstream>

char* readFile(char* path) {
  streampos size;
  char* memblock;

  ifstream file(path, ios::in);
  if (file.is_open()) {
    size = file.tellg();
    memblock = new char[size];
    file.seekg(0, ios::beg);
    file.read(memblock, size);
    file.close();

    return memblock;
  }
  return NULL;
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

  Tokenizer tokenizer(av[1]);
  Token curTok;

  do {
    curTok = tokenizer.nextToken();
    std::cout << curTok.value << "\n";
  } while (curTok.type != T_EOF && curTok.type != T_INVALID);

  return (0);
}
