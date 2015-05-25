#pragma once
#include "node.hpp"
#include <vector>
#include <map>

namespace super_ast {
class StructDeclaration;

/**
* Type instances are a singleton
*/
class Type {
public:
  enum Native {
    VOID,
    BOOLEAN,
    INTEGER,
    DOUBLE,
    STRING,
    VECTOR,
    STRUCT
  };

  static Type* Void();
  static Type* Boolean();
  static Type* Integer();
  static Type* Double();
  static Type* String();
  static Type* Vector(Type* subtype);
  static Type* Struct(StructDeclaration* struct_declaration);
  static Type* ByName(const std::string& name);

  bool is(Native type) const;
  bool operator==(const Type& type) const;
  bool operator!=(const Type& type);
  virtual std::string Representation() const;

private:
  Native type_;
  Declaration* type_definition_;
  std::vector<Type*> subtypes_;

  Type(Native type);
  Type(Native type, const std::vector<Type*>& subtypes);
  Type(Native type, Declaration* type_definition);
  Type& operator=(const Type&);

  static std::map<Native, Type*> types_;
  static Type* get(Native type);
};
}
