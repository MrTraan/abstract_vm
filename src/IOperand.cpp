#include <IOperand.hpp>
#include <Operand.hpp>

IOperand const* createOperand(eOperandType type, std::string const& value) {
  switch (type) {
    case INT_8:
      return new Operand<char>(INT_8, std::stod(value));
    case INT_16:
      return new Operand<int16_t>(INT_16, std::stod(value));
    case INT_32:
      return new Operand<int32_t>(INT_32, std::stod(value));
    case FLOAT:
      return new Operand<float>(FLOAT, std::stod(value));
    case DOUBLE:
      return new Operand<float>(DOUBLE, std::stod(value));
    default:
      return NULL;
  }
}