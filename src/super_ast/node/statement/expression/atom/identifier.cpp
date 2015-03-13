#include "identifier.hpp"
#include <sstream>

namespace super_ast {

Identifier::Identifier(const std::string& value) : value_(value) {

}


const std::string& Identifier::value() const {
  return value_;
}


std::string Identifier::Representation() const {
  std::stringstream ss;
  ss << "ID(" << value_ << ")";
  return ss.str();
}

ACCEPT_SELF_IMPL(Identifier)

}