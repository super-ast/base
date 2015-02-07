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

void Block::PrintChildren(unsigned int depth) const {
  for(int i = 0; i < statements_.size(); ++i) {
    statements_[i]->Print(depth);
  }
}

std::string Block::Representation() const {
  return "BLOCK";
}
}
