#pragma once
#include "../node.hpp"
#include <vector>
#include <map>

namespace super_ast {
/**
* Type instances are a singleton
*/
class Type : public Node {
public:
  static Type* Void();
  static Type* Boolean();
  static Type* Integer();
  static Type* Double();
  static Type* String();
  static Type* Vector(Type* subtype);

  bool operator==(const Type& type);
  bool operator!=(const Type& type);
  virtual std::string Representation() const;

protected:
  ACCEPT_SELF

private:
  enum Native {
    VOID,
    BOOLEAN,
    INTEGER,
    DOUBLE,
    STRING,
    VECTOR
  };

  Native type_;
  std::vector<Type*> subtypes_;

  Type(Native type);
  Type(Native type, const std::vector<Type*>& subtypes);
  Type& operator=(const Type&);

  static std::map<Native, Type*> types_;
  static Type* get(Native type);
};
}
