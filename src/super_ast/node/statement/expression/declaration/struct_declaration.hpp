#pragma once

#include "../declaration.hpp"
#include "variable_declaration.hpp"
#include <vector>

namespace super_ast {
class StructDeclaration : public Declaration {
public:
  typedef Declaration super;
  StructDeclaration(const std::string& name, const std::vector<VariableDeclaration*>& attributes);

  ~StructDeclaration();

  const std::vector<VariableDeclaration*> attributes() const;
  std::string Representation() const;

  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor) const;

private:
  // Maybe we could use a map if we need to reference attributes by its name (?)
  std::vector<VariableDeclaration*> attributes_;
};
}
