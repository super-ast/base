#pragma once
#include "../statement.hpp"
#include "expression.hpp"

namespace super_ast {
class Return : public Statement {
public:
  Return(Expression* value);

  const Expression& value() const;

  std::string Representation() const;

  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor) const;
  virtual bool HasChildren() const;

private:
  Expression* value_;
};
}
