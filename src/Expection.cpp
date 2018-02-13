#include "Exception.hpp"

Exception::Exception(std::string const& msg) throw() : _msg(msg), _prefix("Error: ") {}

Exception::~Exception() throw() {}

const char* Exception::what() const throw() {
	return (_prefix + _msg).c_str();
}

SyntaxException::SyntaxException(std::string const& msg) throw() : Exception(msg) {
	_prefix = "Syntax Error: ";
}

RuntimeException::RuntimeException(std::string const& msg) throw() : Exception(msg) {
	_prefix = "Runtime Error: ";
}

AssertionException::AssertionException(std::string const& msg) throw() : Exception(msg) {
	_prefix = "Assertion Error: ";
}
