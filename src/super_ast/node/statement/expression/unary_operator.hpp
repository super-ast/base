#pragma once

#include "../expression.hpp"

namespace super_ast {
class UnaryOperator : public Expression {
public:
  enum Type {
    NOT
  };

  UnaryOperator(Type type, Expression* expression);

  Type type() const;
  const Expression& expression() const;

  std::string Representation() const;

protected:
  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor, int depth) const;

private:
  Type type_;
  Expression* expression_;
};
}
