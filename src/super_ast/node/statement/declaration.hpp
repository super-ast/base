#pragma once

#include "../statement.hpp"
#include <string>

namespace super_ast {
class Declaration : public Statement {
public:
  Declaration(const std::string& name);

  const std::string& name() const;

private:
  std::string name_;
};
}
