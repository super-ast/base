#pragma once

#include "../loop.hpp"
#include "../expression.hpp"

namespace super_ast {
class For : public Loop {
public:
  typedef Loop super;
  For(Expression* initialization, Expression* condition,
      Expression* post_iteration, Block* body);

  ~For();

  const Expression& initialization() const;
  const Expression& condition() const;
  const Expression& post_iteration() const;

  std::string Representation() const;

protected:
  virtual void AcceptChildren(Visitor& visitor, bool in_preorder, int depth) const;

private:
  Expression* initialization_;
  Expression* condition_;
  Expression* post_iteration_;
};
}
