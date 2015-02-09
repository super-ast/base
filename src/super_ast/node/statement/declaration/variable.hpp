#pragma once

#include "../declaration.hpp"

namespace super_ast {
class Variable : public Declaration {
public:
  Variable(const std::string& name, DataType variable_type);

  ~Variable();

  DataType variable_type() const;

private:
  DataType variable_type_;
};
}
