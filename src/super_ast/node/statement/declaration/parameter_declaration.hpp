#pragma once

#include "../declaration.hpp"

namespace super_ast {
class ParameterDeclaration : public Declaration {
public:
  typedef Declaration super;
  ParameterDeclaration(const std::string& name, DataType parameter_type);

  ~ParameterDeclaration();

  DataType parameter_type() const;

private:
  DataType parameter_type_;
};
}
