#include "block.hpp"

namespace super_ast{
Block::Block() {

}

Block::~Block() {
  for(int i = 0; i < statements_.size(); ++i) {
    delete statements_[i];
  }
}

void Block::AppendStatement(Statement* statement) {
  statements_.push_back(statement);
}

std::string Block::Representation() const {
  return "BLOCK";
}

const std::vector<Statement*>& Block::statements() const {
  return statements_;
}

void Block::AcceptChildren(Visitor& visitor, int depth) const {
  for(const Statement* statement : statements_) {
    statement->Accept(visitor, depth);
  }
}

ACCEPT_SELF_IMPL(Block)

}
