#pragma once

#include "../node.hpp"
#include "statement.hpp"
#include <vector>

namespace super_ast {
/**
* A block is a list of statements
*/
class Block : public Node {
public:
  Block();

  ~Block();

  void AppendStatement(Statement* statement);

  const std::vector<Statement*>& statements() const;
  virtual std::string Representation() const;

  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor) const;
  virtual bool HasChildren() const;

private:
  std::vector<Statement*> statements_;
};
}
