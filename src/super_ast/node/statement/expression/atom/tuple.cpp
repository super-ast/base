#include "tuple.hpp"

namespace super_ast {

Tuple::Tuple(const std::vector<Expression*>& values) : values_(values) {

}

const std::vector<Expression*>& Tuple::values() const {
  return values_;
}

std::string Tuple::Representation() const {
  return "TUPLE";
}

ACCEPT_SELF_IMPL(Tuple)

void Tuple::AcceptChildren(Visitor &visitor) const {
  for(const Expression* value : values_) {
    value->Accept(visitor);
  }
}
}
