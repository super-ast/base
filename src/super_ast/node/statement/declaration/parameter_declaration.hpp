#pragma once

#include "../declaration.hpp"
#include "../../type.hpp"

namespace super_ast {
class ParameterDeclaration : public Declaration {
public:
  typedef Declaration super;
  ParameterDeclaration(const std::string& name, Type* parameter_type);

  ~ParameterDeclaration();

  const Type& parameter_type() const;

  std::string Representation() const;


private:
  Type* parameter_type_;
};
}
