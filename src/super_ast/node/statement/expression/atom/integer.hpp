#pragma once
#include "../atom.hpp"

namespace super_ast {
class Integer : public Atom {
public:
  Integer(int value);

  int value() const;

  std::string Representation() const;

private:
  int value_;
};
}
