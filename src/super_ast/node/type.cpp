#include <sstream>
#include "type.hpp"

namespace super_ast {
namespace {
std::map<Type*, Type*> vector_types;
const std::string NativeStrings[] = {
    "void",
    "bool",
    "int",
    "double",
    "string",
    "vector"
};
}

std::map<Type::Native, Type*> Type::types_;

Type::Type(Native type) : type_(type) {

}

Type::Type(Native type, const std::vector<Type*>& subtypes) : type_(type), subtypes_(subtypes) {

}

std::string Type::Representation() const {
  std::stringstream ss;
  ss << NativeStrings[type_];

  if(subtypes_.size() > 0) {
    ss << '[';

    for(int i = 0; i < subtypes_.size(); ++i) {
      if (i != 0)
        ss << ", ";

      ss << subtypes_[i]->Representation();
    }

    ss << ']';
  }

  return ss.str();
}

bool Type::operator==(const Type& type) {
  if(type_ != type.type_ || subtypes_.size() != type.subtypes_.size())
    return false;

  for(int i = 0; i < subtypes_.size(); ++i) {
    if(*subtypes_[i] != *type.subtypes_[i]) {
      return false;
    }
  }

  return true;
}

bool Type::operator!=(const Type& type) {
  return !(operator==(type));
}

Type* Type::Void() {
  return get(VOID);
}

Type* Type::Boolean() {
  return get(BOOLEAN);
}

Type* Type::Integer() {
  return get(INTEGER);
}

Type* Type::Double() {
  return get(DOUBLE);
}

Type* Type::String() {
  return get(STRING);
}

Type* Type::Vector(Type* subtype) {
  if(vector_types.find(subtype) != vector_types.end())
    return vector_types[subtype];

  Type* vector_type = new Type(VECTOR, {subtype});
  vector_types[subtype] = vector_type;
  return vector_type;
}

Type* Type::get(Type::Native type) {
  if(types_.find(type) != types_.end())
    return types_[type];

  Type* type_ = new Type(type);
  types_[type] = type_;
  return type_;
}
}
