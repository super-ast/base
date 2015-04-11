#include "node.hpp"
#include <iostream>

namespace super_ast {
Node::Node() : id_(0) {

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

unsigned int Node::id() const {
  return id_;
}

void Node::set_id(unsigned int id) {
  id_ = id;
}
}
