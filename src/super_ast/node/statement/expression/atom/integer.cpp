#include <sstream>
#include "integer.hpp"

namespace super_ast {
Integer::Integer(int value) : value_(value) {

}

int Integer::value() const {
  return value_;
}

std::string Integer::Representation() const {
  std::stringstream ss;
  ss << "INT(" << value_ << ")";
  return ss.str();
}
}
