#pragma once

#include "../declaration.hpp"
#include "parameter_declaration.hpp"
#include "../../block.hpp"
#include <vector>

namespace super_ast {
class FunctionDeclaration : public Declaration {
public:
  typedef Declaration super;
  FunctionDeclaration(const std::string& name, DataType return_type,
      const std::vector<ParameterDeclaration*>& parameters, Block* block);

  ~FunctionDeclaration();

  DataType return_type() const;

  const std::vector<ParameterDeclaration*>& parameters() const;

  const Block& block() const;

private:
  DataType return_type_;
  std::vector<ParameterDeclaration*> parameters_;
  Block* block_;
};
}
