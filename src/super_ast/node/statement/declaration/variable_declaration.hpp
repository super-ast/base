#pragma once

#include "../declaration.hpp"
#include "../../type.hpp"

namespace super_ast {
class VariableDeclaration : public Declaration {
public:
  typedef Declaration super;
  VariableDeclaration(const std::string& name, Type* data_type);

  ~VariableDeclaration();

  const Type& data_type() const;

  std::string Representation() const;


private:
  Type* data_type_;
};
}
