#pragma once

#include <string>
#include "visitor.hpp"

#define ACCEPT_SELF \
  virtual void AcceptSelf(Visitor& visitor, int depth) const;

#define ACCEPT_SELF_IMPL(TYPE) \
  void TYPE::AcceptSelf(Visitor& visitor, int depth) const { \
    visitor.Visit(this, depth); \
  }

namespace super_ast {
class Node {
public:
  Node();

  virtual std::string Representation() const;

  void Accept(Visitor& visitor) const;
  void Accept(Visitor& visitor, int depth) const;

protected:
  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor, int depth) const;
};
}
