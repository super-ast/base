#pragma once
#include "../expression.hpp"

namespace super_ast {
class BinaryOperator : public Expression {
public:
  enum Type {
    ASSIGNMENT,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULO,
    EQUAL,
    GREATER_EQUAL,
    GREATER,
    LESS_EQUAL,
    LESS
  };

  BinaryOperator(Type type, Expression* left, Expression* right);
  ~BinaryOperator();

  Type type() const;
  const Expression& left() const;
  const Expression& right() const;

  virtual std::string Representation() const;

protected:
  virtual void PrintChildren(unsigned int depth) const;

private:
  Type type_;
  Expression* left_;
  Expression* right_;
};
}
