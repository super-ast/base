#include <sstream>
#include "function_declaration.hpp"

namespace super_ast {
FunctionDeclaration::FunctionDeclaration(const std::string& name, Type* return_type,
    const std::vector<ParameterDeclaration*>& parameters, Block* body) : super(name), return_type_(return_type),
    parameters_(parameters), body_(body) {

}

FunctionDeclaration::~FunctionDeclaration() {
  for(ParameterDeclaration* parameter : parameters_) {
    delete parameter;
  }

  delete body_;
}

const Type& FunctionDeclaration::return_type() const {
  return *return_type_;
}


const std::vector<ParameterDeclaration*>& FunctionDeclaration::parameters() const {
  return parameters_;
}


const Block& FunctionDeclaration::body() const {
  return *body_;
}


std::string FunctionDeclaration::Representation() const {
  std::stringstream ss;
  ss << "FUNCTION " << return_type_->Representation() << " " << name();
  return ss.str();
}

void FunctionDeclaration::PrintChildren(unsigned int depth) const {
  for(ParameterDeclaration* parameter : parameters_) {
    parameter->Print(depth);
  }

  body_->Print(depth);
}
}
