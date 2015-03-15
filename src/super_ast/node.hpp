#pragma once

#include <string>
#include "visitor.hpp"

#define ACCEPT_SELF \
  virtual void Accept(Visitor& visitor) const;

#define ACCEPT_SELF_IMPL(TYPE) \
  void TYPE::Accept(Visitor& visitor) const { \
    visitor.Visit(this); \
  }

namespace super_ast {
class Node {
public:
  Node();

  virtual std::string Representation() const;

  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor) const;
  virtual bool HasChildren() const;
};
}
