#pragma once

#include "../node.hpp"
#include "../type.hpp"

namespace super_ast {
class TypeReference : public Node {
public:
  TypeReference(Type* type);

  const Type& referenced_type() const;

  virtual std::string Representation() const;

  ACCEPT_SELF

private:
  Type* referenced_type_;
};
}
