#pragma once

#include <iostream>

enum eOperandType { INT_8 = 0, INT_16 = 1, INT_32 = 2, FLOAT = 3, DOUBLE = 4 };

class IOperand {
 public:
  virtual int getPrecision() const = 0;
  virtual eOperandType getType() const = 0;

  virtual IOperand const* operator+(IOperand const& rhs) const = 0;
  virtual IOperand const* operator-(IOperand const& rhs) const = 0;
  virtual IOperand const* operator*(IOperand const& rhs) const = 0;
  virtual IOperand const* operator/(IOperand const& rhs) const = 0;
  virtual IOperand const* operator%(IOperand const& rhs) const = 0;

  virtual std::string const& toString() const = 0;

  virtual ~IOperand(void) {}
};
