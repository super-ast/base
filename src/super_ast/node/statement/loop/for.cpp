#include "for.hpp"

namespace super_ast {

For::For(Expression* initialization, Expression* condition, Expression* post_iteration, Block* body)
    : super(body), initialization_(initialization), condition_(condition), post_iteration_(post_iteration) {

}

For::~For() {
  delete initialization_;
  delete condition_;
  delete post_iteration_;
}

const Expression& For::initialization() const {
  return *initialization_;
}

const Expression& For::condition() const {
  return *condition_;
}

const Expression& For::post_iteration() const {
  return *post_iteration_;
}

std::string For::Representation() const {
  return "FOR";
}

ACCEPT_SELF_IMPL(For)

void For::AcceptChildren(Visitor& visitor, int depth) const {
  initialization_->Accept(visitor, depth);
  condition_->Accept(visitor, depth);
  post_iteration_->Accept(visitor, depth);
  super::AcceptChildren(visitor, depth);
}
}
