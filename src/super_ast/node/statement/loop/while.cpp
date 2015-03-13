#include "while.hpp"

namespace super_ast {

While::While(Expression* condition, Block* body) : super(body), condition_(condition) {

}


While::~While() {
  delete condition_;
}

const Expression& While::condition() const {
  return *condition_;
}

std::string While::Representation() const {
  return "WHILE";
}

ACCEPT_SELF_IMPL(While)

void While::AcceptChildren(Visitor& visitor, int depth) const {
  condition_->Accept(visitor, depth);
  super::AcceptChildren(visitor, depth);
}
}
