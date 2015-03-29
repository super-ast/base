#pragma once

#include "../declaration.hpp"
#include "../../../type.hpp"

namespace super_ast {
class VariableDeclaration : public Declaration {
public:
  typedef Declaration super;
  VariableDeclaration(const std::string& name, Type* data_type, bool is_reference, Expression* initialization);

  ~VariableDeclaration();

  const Type& data_type() const;
  bool is_reference() const;
  bool HasInitialization() const;
  const Expression& initialization() const;

  std::string Representation() const;

  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor) const;

private:
  Type* data_type_;
  bool is_reference_;
  Expression* initialization_;
};
}
