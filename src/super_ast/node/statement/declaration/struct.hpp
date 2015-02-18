#pragma once

#include "../declaration.hpp"
#include "variable_declaration.hpp"
#include <vector>

namespace super_ast {
class Struct : public Declaration {
public:
  Struct(const std::string& name);

  ~Struct();

  void AddAttribute(Struct* attribute);

  const std::vector<VariableDeclaration*> attributes() const;

private:
  // Maybe we could use a map if we need to reference attributes by its name (?)
  std::vector<VariableDeclaration*> attributes_;
};
}
