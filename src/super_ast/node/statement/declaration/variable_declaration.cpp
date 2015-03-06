#include "variable_declaration.hpp"
#include <sstream>

namespace super_ast {
VariableDeclaration::VariableDeclaration(const std::string& name, Type* data_type, bool is_reference) :
    super(name), data_type_(data_type), is_reference_(is_reference) {

}

VariableDeclaration::~VariableDeclaration() {

}


const Type& VariableDeclaration::data_type() const {
  return *data_type_;
}

bool VariableDeclaration::is_reference() const {
  return is_reference_;
}

std::string VariableDeclaration::Representation() const {
  std::stringstream ss;
  ss << "VAR " << data_type_->Representation() << " " << name();
  return ss.str();
}
}
