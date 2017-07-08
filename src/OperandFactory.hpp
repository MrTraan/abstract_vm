#pragma once

#include <IOperand.hpp>
#include <Operand.hpp>

class OperandFactory {
 public:
  OperandFactory(void);
  OperandFactory(const OperandFactory& src);
  ~OperandFactory(void);

  OperandFactory& operator=(const OperandFactory& rhs);

  IOperand const* createOperand(eOperandType type, std::string const& value);

 private:
  IOperand const* createInt8(std::string const& value);
  IOperand const* createInt16(std::string const& value);
  IOperand const* createInt32(std::string const& value);
  IOperand const* createFloat(std::string const& value);
  IOperand const* createDouble(std::string const& value);
  IOperand const* (OperandFactory::*_operandTypeToMethod[5])(
      std::string const&);
};
