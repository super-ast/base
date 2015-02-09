#pragma once

#include "../declaration.hpp"
#include "../../type.hpp"

namespace super_ast {
class Variable : public Declaration {
public:
  Variable(const std::string& name, Type* variable_type);

  ~Variable();

  const Type& variable_type() const;

private:
  Type* variable_type_;
};
}
