#include "function_declaration.hpp"

namespace super_ast {
FunctionDeclaration::FunctionDeclaration(const std::string& name, Type* return_type,
    const std::vector<VariableDeclaration*>& parameters, Block* body) : super(name), return_type_(return_type),
    parameters_(parameters), body_(body) {

}

FunctionDeclaration::~FunctionDeclaration() {
  for(VariableDeclaration* parameter : parameters_) {
    delete parameter;
  }

  delete body_;
}

const Type& FunctionDeclaration::return_type() const {
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

void FunctionDeclaration::AcceptChildren(Node::Visitor& visitor, bool in_preorder, int depth) const {
  for(VariableDeclaration* parameter : parameters_) {
    parameter->Accept(visitor, in_preorder, depth);
  }

  body_->Accept(visitor, in_preorder, depth);
}
}
