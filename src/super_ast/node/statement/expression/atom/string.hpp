#pragma once
#include "../atom.hpp"

namespace super_ast {
class String : public Atom {
public:
  String(const std::string& value);

  const std::string& value() const;

  std::string Representation() const;

  static std::string Escape(const std::string& str);

private:
  std::string value_;
};
}
