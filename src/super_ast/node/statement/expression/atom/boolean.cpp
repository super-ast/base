#include "boolean.hpp"

namespace super_ast {

Boolean::Boolean(bool value) : value_(value) {

}


bool Boolean::value() const {
  return value_;
}


std::string Boolean::Representation() const {
  return std::string("BOOLEAN(") + std::string(value_ ? "true" : "false") + std::string(")");
}

ACCEPT_SELF_IMPL(Boolean)
}
