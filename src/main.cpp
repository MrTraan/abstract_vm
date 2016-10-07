#include <iostream>
#include <Int32.hpp>

int main(void) {

  Int32 a(14);
  Int32 b(16);

  const IOperand *c = a + b;

  std::cout << c->toString() << "\n";
  return (0);
}
