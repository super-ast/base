#pragma once

#include "../block.hpp"
#include "expression.hpp"
#include <string>

namespace super_ast {
class Conditional : public Statement {
public:
  Conditional(Expression* condition, Block* then_block);

  Conditional(Expression* condition, Block* then_block, Block* else_block);

  ~Conditional();

  const Expression& condition() const;
  const Block& then_block() const;
  bool has_else_block() const;
  const Block& else_block() const;

  std::string Representation() const;

  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor) const;
  virtual bool HasChildren() const;

private:
  Expression* condition_;
  Block* then_block_;
  Block* else_block_;
};
}
