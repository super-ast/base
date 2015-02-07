#pragma once

#include "../declaration.hpp"

namespace super_ast {
class Parameter : public Declaration {
public:
  Parameter(const std::string& name, DataType parameter_type);

  ~Parameter();

  DataType parameter_type() const;

private:
  DataType parameter_type_;
};
}
