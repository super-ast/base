#pragma once
#include "../atom.hpp"

namespace super_ast {
class Identifier : public Atom {
public:
  Identifier(const std::string& value);

  const std::string& value() const;

  std::string Representation() const;

private:
  std::string value_;
};
}
