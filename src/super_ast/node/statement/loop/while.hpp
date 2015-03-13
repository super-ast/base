#pragma once

#include "../loop.hpp"
#include "../expression.hpp"

namespace super_ast {
class While : public Loop {
public:
  typedef Loop super;
  While(Expression* condition, Block* body);

  ~While();

  const Expression& condition() const;

  std::string Representation() const;

protected:
  virtual void AcceptChildren(Visitor& visitor, bool in_preorder, int depth) const;

private:
  Expression* condition_;
};
}
