#include "node.hpp"
#include <iostream>

namespace super_ast {
Node::Node() {

}

std::string Node::Representation() const {
  return "UNKNOWN";
}

void Node::Accept(Visitor& visitor) const {
    visitor.Visit(this);
}

void Node::AcceptChildren(Visitor& visitor) const {
  // Do nothing
}

bool Node::HasChildren() const {
  return false;
}
}
