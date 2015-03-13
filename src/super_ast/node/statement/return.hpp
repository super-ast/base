#pragma once
#include "../statement.hpp"
#include "expression.hpp"

namespace super_ast {
class Return : public Statement {
public:
  Return(Expression* value);

  const Expression& value() const;

  std::string Representation() const;

protected:
  virtual void AcceptChildren(Visitor& visitor, int depth) const;

private:
  Expression* value_;
};
}
