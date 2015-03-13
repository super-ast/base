#pragma once

#include <string>

namespace super_ast {
class Node {
public:
  static bool PRE_ORDER;
  static bool POST_ORDER;

  class Visitor {
  public:
    virtual void Visit(const Node& node, int depth);
  };

  Node();

  virtual std::string Representation() const;

  void Accept(Visitor& visitor, bool in_preoder) const;
  void Accept(Visitor& visitor, bool in_preorder, int depth) const;

protected:
  virtual void AcceptChildren(Visitor& visitor, bool in_preorder, int depth) const;
};
}
