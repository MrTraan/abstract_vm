#include <iostream>
#include <IOperand.hpp>

int main(void) {
  std::string const tab[2] = {"3.67", "-1.3"};
  IOperand const* a = createOperand(FLOAT, tab[0]);
  IOperand const* b = createOperand(FLOAT, tab[1]);

  IOperand const* plus = *a + *b;
  IOperand const* minus = *a - *b;
  IOperand const* times = *a * *b;
  IOperand const* divide = *a / *b;

  std::cout << "14 + 16: " << plus->toString() << "\n";
  std::cout << "14 - 16: " << minus->toString() << "\n";
  std::cout << "14 * 16: " << times->toString() << "\n";
  std::cout << "14 / 16: " << divide->toString() << "\n";

  delete plus;
  delete minus;
  delete times;
  delete divide;

  return (0);
}
