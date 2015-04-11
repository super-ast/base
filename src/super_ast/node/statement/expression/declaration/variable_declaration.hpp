#pragma once

#include "../declaration.hpp"
#include "../../../type_reference.hpp"

namespace super_ast {
class VariableDeclaration : public Declaration {
public:
  typedef Declaration super;
  VariableDeclaration(const std::string& name, TypeReference* data_type,
                      bool is_reference, bool is_constant, Expression* initialization);

  ~VariableDeclaration();

  const TypeReference& data_type() const;

  bool is_reference() const;
  bool is_constant() const;

  bool HasInitialization() const;
  const Expression& initialization() const;

  std::string Representation() const;

  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor) const;

private:
  TypeReference* data_type_;
  bool is_reference_;
  bool is_constant_;
  Expression* initialization_;
};
}
