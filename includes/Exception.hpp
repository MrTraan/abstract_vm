#pragma once

#include <string>
#include <exception>

class Exception : public std::exception {
 public:
  Exception(std::string const& msg) throw();
  virtual ~Exception() throw();

  virtual const char* what() const throw();

 private:
  std::string _msg;
};