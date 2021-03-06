#include "function_declaration.hpp"

namespace super_ast {
FunctionDeclaration::FunctionDeclaration(const std::string& name, TypeReference* return_type,
    const std::vector<VariableDeclaration*>& parameters, Block* body) : super(name), return_type_(return_type),
    parameters_(parameters), body_(body) {

}

FunctionDeclaration::~FunctionDeclaration() {
  for(VariableDeclaration* parameter : parameters_) {
    delete parameter;
  }

  delete body_;
}

const TypeReference& FunctionDeclaration::return_type() const {
  return *return_type_;
}


const std::vector<VariableDeclaration*>& FunctionDeclaration::parameters() const {
  return parameters_;
}


const Block& FunctionDeclaration::body() const {
  return *body_;
}


std::string FunctionDeclaration::Representation() const {
  return std::string("FUNCTION ") + return_type_->Representation() + std::string(" ") + name();
}

ACCEPT_SELF_IMPL(FunctionDeclaration)

void FunctionDeclaration::AcceptChildren(Visitor& visitor) const {
  for(VariableDeclaration* parameter : parameters_) {
    parameter->Accept(visitor);
  }

  body_->Accept(visitor);
}

bool FunctionDeclaration::HasChildren() const {
  return true;
}
}
