#include "variable_declaration.hpp"
#include <sstream>

namespace super_ast {
VariableDeclaration::VariableDeclaration(const std::string& name, Type* data_type) :
    super(name), data_type_(data_type) {

}

VariableDeclaration::~VariableDeclaration() {

}


const Type& VariableDeclaration::data_type() const {
  return *data_type_;
}

std::string VariableDeclaration::Representation() const {
  std::stringstream ss;
  ss << "VAR " << data_type_->Representation() << " " << name();
  return ss.str();
}
}
