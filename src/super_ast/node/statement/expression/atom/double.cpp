#include "double.hpp"
#include <sstream>

namespace super_ast {

Double::Double(double value) : value_(value) {

}

double Double::value() const {
  return value_;
}

std::string Double::Representation() const {
  std::stringstream ss;
  ss << "DOUBLE(" << value_ << ")";
  return ss.str();
}

ACCEPT_SELF_IMPL(Double)
}
