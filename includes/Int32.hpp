#pragma once

#include <IOperand.hpp>

class Int32 : public IOperand {
public:
  Int32(int32_t val) : value(val){};
  eOperandType getType() const;
  // int getPrecision() const;
  int getValue() const;

  IOperand const *operator+(IOperand const &rhs) const;
  //   IOperand const *operator-(IOperand const &rhs) const;
  //   IOperand const *operator*(IOperand const &rhs) const;
  //   IOperand const *operator/(IOperand const &rhs) const;
  //   IOperand const *operator%(IOperand const &rhs) const;

  std::string const &toString() const;

private:
  int32_t value;
};