#pragma once

#include "../atom.hpp"

namespace super_ast {
class NotSupported : public Atom {
public:
  enum TYPE {
    WARNING,
    ERROR
  };

  NotSupported(TYPE type, const std::string& value, const std::string& description);

  const std::string& value() const;
  const std::string& description() const;

  std::string Representation() const;

  ACCEPT_SELF

private:
  TYPE type_;
  std::string value_;
  std::string description_;
};
}
