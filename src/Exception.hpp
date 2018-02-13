#pragma once

#include <string>
#include <exception>

class Exception : public std::exception {
	public:
		Exception(std::string const& msg) throw();
		virtual ~Exception() throw();

		virtual const char* what() const throw();

	protected:
		std::string _msg;
		std::string _prefix;
};

class SyntaxException : public Exception {
	public:
		SyntaxException(std::string const& msg) throw();
};

class RuntimeException : public Exception {
	public:
		RuntimeException(std::string const& msg) throw();
};

class AssertionException : public Exception {
	public:
		AssertionException(std::string const& msg) throw();
};
