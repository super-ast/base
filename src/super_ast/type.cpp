#include <sstream>
#include "type.hpp"
#include "node/statement/expression/declaration/struct_declaration.hpp"

namespace super_ast {
namespace {
std::map<Type*, Type*> vector_types;
std::map<std::string, Type*> named_types;

const std::string NativeStrings[] = {
    "void",
    "bool",
    "int",
    "double",
    "string",
    "vector",
    "struct",
    "tuple"
};
}

std::map<Type::Native, Type*> Type::types_;

Type::Type(Native type) : type_(type), type_definition_(0) {

}

Type::Type(Native type, const std::vector<Type*>& subtypes) : type_(type), subtypes_(subtypes), type_definition_(0) {

}


Type::Type(Type::Native type, Declaration* type_definition) : type_(type), type_definition_(type_definition) {

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

  if(type_definition_) {
    ss << '[' << type_definition_->name() << ']';
  }

  return ss.str();
}

bool Type::is(Native type) const {
  return type_ == type;
}

bool Type::operator==(const Type& type) const {
  if(!is(type.type_) || type_definition_ != type.type_definition_ || subtypes_.size() != type.subtypes_.size())
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

Type* Type::Struct(StructDeclaration* struct_declaration) {
  if(named_types.find(struct_declaration->name()) != named_types.end())
    return named_types[struct_declaration->name()];

  Type* struct_type = new Type(STRUCT, struct_declaration);
  named_types[struct_declaration->name()] = struct_type;
  return struct_type;
}


Type *Type::Tuple(const std::vector<Type*> &subtypes) {
  return new Type(TUPLE, subtypes);
}

Type* Type::ByName(const std::string& name) {
  std::map<std::string, Type*>::const_iterator it = named_types.find(name);

  if(it != named_types.end())
    return it->second;

  return 0;
}

Type* Type::get(Type::Native type) {
  if(types_.find(type) != types_.end())
    return types_[type];

  Type* type_ = new Type(type);
  types_[type] = type_;
  return type_;
}
}
