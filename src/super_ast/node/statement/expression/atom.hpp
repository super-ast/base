#pragma once
#include "../expression.hpp"

namespace super_ast {
class Atom : public Expression {
public:
  Atom();
  ~Atom();
};
}