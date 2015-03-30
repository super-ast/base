#include "struct_declaration.hpp"

namespace super_ast {

StructDeclaration::StructDeclaration(const std::string& name,
    const std::vector<VariableDeclaration*>& attributes) : super(name), attributes_(attributes) {

}

StructDeclaration::~StructDeclaration() {
  for(VariableDeclaration* attribute : attributes_) {
    delete attribute;
  }
}

const std::vector<VariableDeclaration*> StructDeclaration::attributes() const {
  return attributes_;
}

std::string StructDeclaration::Representation() const {
  return "STRUCT " + std::string(name());
}

ACCEPT_SELF_IMPL(StructDeclaration);

void StructDeclaration::AcceptChildren(Visitor& visitor) const {
  for(VariableDeclaration* attribute : attributes_) {
    attribute->Accept(visitor);
  }
}
}
