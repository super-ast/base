#include "return.hpp"

namespace super_ast {

Return::Return(Expression* value) : value_(value) {
}

const Expression& Return::value() const {
  return *value_;
}

std::string Return::Representation() const {
  return "RETURN";
}

ACCEPT_SELF_IMPL(Return)

void Return::AcceptChildren(Visitor& visitor) const {
  value_->Accept(visitor);
}

bool Return::HasChildren() const {
  return true;
}
}
