#pragma once

#include "../declaration.hpp"
#include "variable_declaration.hpp"
#include "../../../block.hpp"
#include <vector>

namespace super_ast {
class FunctionDeclaration : public Declaration {
public:
  typedef Declaration super;
  FunctionDeclaration(const std::string& name, TypeReference* return_type,
      const std::vector<VariableDeclaration*>& parameters, Block* body);

  ~FunctionDeclaration();

  const TypeReference& return_type() const;
  const std::vector<VariableDeclaration*>& parameters() const;
  const Block& body() const;

  virtual std::string Representation() const;

  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor) const;
  virtual bool HasChildren() const;

private:
  TypeReference* return_type_;
  std::vector<VariableDeclaration*> parameters_;
  Block* body_;
};
}
