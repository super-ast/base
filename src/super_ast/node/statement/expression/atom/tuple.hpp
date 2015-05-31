#pragma once

#include <vector>
#include "../atom.hpp"

namespace super_ast {
class Tuple : public Atom {
public:
  Tuple(const std::vector<Expression*>& values);

  const std::vector<Expression*>& values() const;

  std::string Representation() const;

  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor) const;

private:
  std::vector<Expression*> values_;
};
}
