#include "node.hpp"
#include <iostream>

namespace super_ast {
Node::Node() {

}

std::string Node::Representation() const {
  return "UNKNOWN";
}

void Node::Accept(Visitor& visitor) const {
  Accept(visitor, 0);
}

void Node::Accept(Visitor& visitor, int depth) const {
  if(visitor.in_pre_order()) {
    AcceptSelf(visitor, depth);
    AcceptChildren(visitor, depth+1);
  } else {
    AcceptChildren(visitor, depth);
    AcceptSelf(visitor, depth+1);
  }
}

ACCEPT_SELF_IMPL(Node)

void Node::AcceptChildren(Visitor& visitor, int depth) const {
  // Do nothing
}
}
