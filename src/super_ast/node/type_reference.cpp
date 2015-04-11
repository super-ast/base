#include "type_reference.hpp"

namespace super_ast {
TypeReference::TypeReference(Type* type) : referenced_type_(type) {

}

const Type& TypeReference::referenced_type() const {
  return *referenced_type_;
}

std::string TypeReference::Representation() const {
  return referenced_type_->Representation();
}

ACCEPT_SELF_IMPL(TypeReference)
}
