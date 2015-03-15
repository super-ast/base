#include "loop.hpp"

namespace super_ast {

Loop::Loop(Block* body) : body_(body) {

}

Loop::~Loop() {
  delete body_;
}

const Block& Loop::body() const {
  return *body_;
}

std::string Loop::Representation() const {
  return "LOOP";
}

ACCEPT_SELF_IMPL(Loop)

void Loop::AcceptChildren(Visitor& visitor) const {
  body_->Accept(visitor);
}

bool Loop::HasChildren() const {
  return true;
}
}
