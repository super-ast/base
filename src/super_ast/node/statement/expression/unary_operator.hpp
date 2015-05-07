#pragma once

#include "../expression.hpp"

namespace super_ast {
class UnaryOperator : public Expression {
public:
  enum Type {
    NOT,
    NEG,
    POS,
    PRE_INCREMENT,
    POST_INCREMENT,
    PRE_DECREMENT,
    POST_DECREMENT
  };

  UnaryOperator(Type type, Expression* expression);

  Type type() const;
  const Expression& expression() const;

  std::string Representation() const;

  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor) const;
  virtual bool HasChildren() const;

private:
  Type type_;
  Expression* expression_;
};
}
