#include "node.hpp"
#include <iostream>

namespace super_ast {
void Node::Visitor::Visit(const Node& node, int depth) {
  // Do nothing
}

bool Node::PRE_ORDER = true;
bool Node::POST_ORDER = false;

Node::Node() {

}

std::string Node::Representation() const {
  return "UNKNOWN";
}

void Node::Accept(Node::Visitor& visitor, bool in_preoder) const {
  Accept(visitor, in_preoder, 0);
}

void Node::Accept(Visitor& visitor, bool in_preorder, int depth) const {
  if(in_preorder) {
    visitor.Visit(*this, depth);
  }

  AcceptChildren(visitor, in_preorder, depth+1);

  if(!in_preorder) {
    visitor.Visit(*this, depth);
  }
}

void Node::AcceptChildren(Node::Visitor& visitor, bool in_preorder, int depth) const {
  // Do nothing
}
}
