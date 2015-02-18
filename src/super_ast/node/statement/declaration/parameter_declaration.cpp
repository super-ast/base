#include "parameter_declaration.hpp"
#include <sstream>

namespace super_ast {
ParameterDeclaration::ParameterDeclaration(const std::string& name, Type* parameter_type) :
    super(name), parameter_type_(parameter_type) {

}

ParameterDeclaration::~ParameterDeclaration() {

}


const Type& ParameterDeclaration::parameter_type() const {
  return *parameter_type_;
}

std::string ParameterDeclaration::Representation() const {
  std::stringstream ss;
  ss << "PARAM " << parameter_type_->Representation() << " " << name();
  return ss.str();
}
}
