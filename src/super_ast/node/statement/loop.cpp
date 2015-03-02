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

void Loop::PrintChildren(unsigned int depth) const {
  body_->Print(depth);
}
}
