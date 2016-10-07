#pragma once

#include <iostream>

typedef enum OperandType { INT_32 = 1 } eOperandType;

class IOperand {
public:
  virtual ~IOperand(){};

  virtual eOperandType getType() const = 0;
  virtual int getValue() const = 0;

  //   virtual int getPrecision() const = 0;
  //   virtual IOperand const *operator+(IOperand const &rhs) const = 0;
  //   virtual IOperand const *operator-(IOperand const &rhs) const = 0;
  //   virtual IOperand const *operator*(IOperand const &rhs) const = 0;
  //   virtual IOperand const *operator/(IOperand const &rhs) const = 0;
  //   virtual IOperand const *operator%(IOperand const &rhs) const = 0;
  virtual std::string const &toString() const = 0;
};