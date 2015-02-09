#pragma once
#include <exception>

namespace super_ast {
class ParseError : public std::exception {
public:
  virtual const char* what() const throw() = 0;
};
}
