#pragma once

#include "../declaration.hpp"
#include "../../type.hpp"

namespace super_ast {
class VariableDeclaration : public Declaration {
public:
  VariableDeclaration(const std::string& name, Type* variable_type);

  ~VariableDeclaration();

  const Type& variable_type() const;

private:
  Type* variable_type_;
};
}
