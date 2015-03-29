#include "variable_declaration.hpp"
#include <sstream>

namespace super_ast {
VariableDeclaration::VariableDeclaration(const std::string& name, Type* data_type, bool is_reference,
    Expression* initialization) : super(name), data_type_(data_type), is_reference_(is_reference),
                                  initialization_(initialization) {

}

VariableDeclaration::~VariableDeclaration() {

}


const Type& VariableDeclaration::data_type() const {
  return *data_type_;
}

bool VariableDeclaration::is_reference() const {
  return is_reference_;
}

bool VariableDeclaration::HasInitialization() const {
  return initialization_ != 0;
}

const Expression& VariableDeclaration::initialization() const {
  return *initialization_;
}

std::string VariableDeclaration::Representation() const {
  return std::string("VAR ") + data_type_->Representation() + std::string(" ") + name();
}

ACCEPT_SELF_IMPL(VariableDeclaration)

void VariableDeclaration::AcceptChildren(Visitor& visitor) const {
  if(HasInitialization()) {
    initialization_->Accept(visitor);
  }
}

}
