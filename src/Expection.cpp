#include "Exception.hpp"

Exception::Exception(std::string const& msg) throw() : _msg(msg) {}

Exception::~Exception() throw() {}

const char* Exception::what() const throw() {
  return (_msg.c_str());
}