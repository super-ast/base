#pragma once

#include "../declaration.hpp"
#include "variable_declaration.hpp"
#include <vector>

namespace super_ast {
class StructDeclaration : public Declaration {
public:
  StructDeclaration(const std::string& name);

  ~StructDeclaration();

  void AddAttribute(StructDeclaration* attribute);

  const std::vector<VariableDeclaration*> attributes() const;

private:
  // Maybe we could use a map if we need to reference attributes by its name (?)
  std::vector<VariableDeclaration*> attributes_;
};
}
