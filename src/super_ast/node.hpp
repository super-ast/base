#pragma once

#include <string>

namespace super_ast {
class Node {
public:
  // This types could be used to analyze and classify different nodes in groups
  enum NodeType {
    UNKNOWN,
    BLOCK,
    DECLARATION,
    PARAMETER,
    LOOP,
    FOR_LOOP,
    WHILE_LOOP,
    EXPRESSION,
    ASSIGNMENT,
    CONDITIONAL
    // ...
  };

  Node();

  ~Node();

  virtual bool is(NodeType type) const;

  virtual std::string Representation() const;

  void Print() const;
  void Print(unsigned int depth) const;

protected:
  virtual void PrintChildren(unsigned int depth) const;
};
}
