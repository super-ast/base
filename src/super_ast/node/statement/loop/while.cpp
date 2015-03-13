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

void While::AcceptChildren(Node::Visitor& visitor, bool in_preorder, int depth) const {
  condition_->Accept(visitor, in_preorder, depth);
  super::AcceptChildren(visitor, in_preorder, depth);
}
}
