#pragma once

#include "../expression.hpp"
#include <string>

namespace super_ast {
class Declaration : public Expression {
public:
  Declaration(const std::string& name);

  const std::string& name() const;

private:
  std::string name_;
};
}
