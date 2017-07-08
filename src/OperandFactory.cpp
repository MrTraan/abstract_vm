#include <OperandFactory.hpp>

OperandFactory::OperandFactory(void) {
  this->_operandTypeToMethod[INT_8] = &OperandFactory::createInt8;
  this->_operandTypeToMethod[INT_16] = &OperandFactory::createInt16;
  this->_operandTypeToMethod[INT_32] = &OperandFactory::createInt32;
  this->_operandTypeToMethod[FLOAT] = &OperandFactory::createFloat;
  this->_operandTypeToMethod[DOUBLE] = &OperandFactory::createDouble;
}

OperandFactory::OperandFactory(const OperandFactory& src) {
  (void)src;
}

OperandFactory::~OperandFactory(void) {}

OperandFactory& OperandFactory::operator=(const OperandFactory& rhs) {
  (void)rhs;
  return *this;
}

IOperand const* OperandFactory::createOperand(eOperandType type,
                                              std::string const& value) {
  return (this->*_operandTypeToMethod[type])(value);
}

IOperand const* OperandFactory::createInt8(std::string const& value) {
  return new Operand<char>(INT_8, std::stod(value));
}

IOperand const* OperandFactory::createInt16(std::string const& value) {
  return new Operand<int16_t>(INT_16, std::stod(value));
}

IOperand const* OperandFactory::createInt32(std::string const& value) {
  return new Operand<int32_t>(INT_32, std::stod(value));
}

IOperand const* OperandFactory::createFloat(std::string const& value) {
  return new Operand<float>(FLOAT, std::stod(value));
}

IOperand const* OperandFactory::createDouble(std::string const& value) {
  return new Operand<float>(DOUBLE, std::stod(value));
}
