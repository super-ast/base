#include "parameter_declaration.hpp"

namespace super_ast {
ParameterDeclaration::ParameterDeclaration(const std::string& name, Type* parameter_type) :
    super(name), parameter_type_(parameter_type) {

}

ParameterDeclaration::~ParameterDeclaration() {

}


const Type& ParameterDeclaration::parameter_type() const {
  return *parameter_type_;
}
}
