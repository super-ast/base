#pragma once

#include "../atom.hpp"

namespace super_ast {
class Double : public Atom {
public:
  Double(double value);

  double value() const;

  std::string Representation() const;

  ACCEPT_SELF

private:
  double value_;
};
}
