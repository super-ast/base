#pragma once

#include "../declaration.hpp"
#include "parameter_declaration.hpp"
#include "../../block.hpp"
#include <vector>

namespace super_ast {
class FunctionDeclaration : public Declaration {
public:
  typedef Declaration super;
  FunctionDeclaration(const std::string& name, Type* return_type,
      const std::vector<ParameterDeclaration*>& parameters, Block* body);

  ~FunctionDeclaration();

  const Type& return_type() const;
  const std::vector<ParameterDeclaration*>& parameters() const;
  const Block& body() const;

  virtual std::string Representation() const;
  virtual void PrintChildren(unsigned int depth) const;

private:
  Type* return_type_;
  std::vector<ParameterDeclaration*> parameters_;
  Block* body_;
};
}
