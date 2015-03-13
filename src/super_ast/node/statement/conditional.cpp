#include "conditional.hpp"

namespace super_ast {

Conditional::Conditional(Expression* condition, Block* then_block)
    : Conditional(condition, then_block, 0) {

}

Conditional::Conditional(Expression* condition, Block* then_block, Block* else_block)
    : condition_(condition), then_block_(then_block), else_block_(else_block) {

}

Conditional::~Conditional() {
  delete condition_;
  delete then_block_;

  if(has_else_block()) {
    delete else_block_;
  }
}

const Expression& Conditional::condition() const {
  return *condition_;
}

const Block& Conditional::then_block() const {
  return *then_block_;
}

bool Conditional::has_else_block() const {
  return else_block_ != 0;
}

const Block& Conditional::else_block() const {
  return *else_block_;
}

std::string Conditional::Representation() const {
  return "CONDITIONAL";
}

ACCEPT_SELF_IMPL(Conditional)

void Conditional::AcceptChildren(Visitor& visitor, int depth) const {
  condition_->Accept(visitor, depth);
  then_block_->Accept(visitor, depth);

  if(has_else_block()) {
    else_block_->Accept(visitor, depth);
  }
}
}
