#include "variable_declaration.hpp"
#include <sstream>

namespace super_ast {
VariableDeclaration::VariableDeclaration(const std::string& name, TypeReference* data_type,
                                         bool is_reference, bool is_constant, Expression* initialization)
    : super(name), data_type_(data_type), is_reference_(is_reference), is_constant_(is_constant),
      initialization_(initialization) {

}

VariableDeclaration::~VariableDeclaration() {
  delete data_type_;

  if(HasInitialization())
    delete initialization_;
}


const TypeReference& VariableDeclaration::data_type() const {
  return *data_type_;
}

bool VariableDeclaration::is_reference() const {
  return is_reference_;
}

bool VariableDeclaration::is_constant() const {
  return is_constant_;
}

bool VariableDeclaration::HasInitialization() const {
  return initialization_ != 0;
}

const Expression& VariableDeclaration::initialization() const {
  return *initialization_;
}

std::string VariableDeclaration::Representation() const {
  std::string representation = "VAR ";

  if(is_constant()) {
    representation += "const ";
  }

  representation += data_type_->Representation();

  if(is_reference()) {
    representation += "&";
  }


  return representation + " " + name();
}

ACCEPT_SELF_IMPL(VariableDeclaration)

void VariableDeclaration::AcceptChildren(Visitor& visitor) const {
  if(HasInitialization()) {
    initialization_->Accept(visitor);
  }
}
}
