#include <Int32.hpp>

eOperandType Int32::getType() const { return INT_32; }

int Int32::getValue() const { return value; }

IOperand const *Int32::operator+(IOperand const &rhs) const {
  return new Int32(this->getValue() + rhs.getValue());
}

std::string const &Int32::toString() const {
  const std::string *s = new std::string(std::to_string(this->value));
  return *s;
}