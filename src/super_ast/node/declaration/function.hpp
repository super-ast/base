#pragma once

#include "../declaration.hpp"
#include "parameter.hpp"
#include "../block.hpp"
#include <vector>

namespace super_ast {
class Function : public Declaration {
public:
  Function(const std::string& name, DataType return_type,
      const std::vector<Parameter*>& parameters, Block* block);

  ~Function();

  DataType return_type() const;

  const std::vector<Parameter*>& parameters() const;

  const Block& block() const;

private:
  DataType return_type_;
  std::vector<Parameter*> parameters_;
  Block* block_;
};
}
