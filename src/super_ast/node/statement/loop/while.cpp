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

void While::PrintChildren(unsigned int depth) const {
  condition_->Print(depth);
  super::PrintChildren(depth);
}
}
