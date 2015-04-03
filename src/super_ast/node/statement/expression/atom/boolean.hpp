#pragma once

#include "../atom.hpp"

namespace super_ast {
class Boolean : public Atom {
public:
  Boolean(bool value);

  bool value() const;

  std::string Representation() const;

  ACCEPT_SELF

private:
  bool value_;
};
}
