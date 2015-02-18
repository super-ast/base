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

void Return::PrintChildren(unsigned int depth) const {
  value_->Print(depth);
}
}
