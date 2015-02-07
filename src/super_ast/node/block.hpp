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

  /**
  * Adds the given statement at the end of this block
  */
  void AppendStatement(Statement* statement);
  virtual void PrintChildren(unsigned int depth) const;


  const std::vector<Statement*>& statements() const;

  virtual std::string Representation() const;

  /**
  * Returns the total number of loops in this block
  */
  int LoopCount() const;

  /**
  * Returns the total number of conditionals in this block
  */
  int ConditionalCount() const;

  // More API here...

private:
  std::vector<Statement*> statements_;
};
}
