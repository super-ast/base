#include "declaration.hpp"

namespace super_ast {
Declaration::Declaration(const std::string& name) : name_(name) {

}

const std::string& Declaration::name() const {
  return name_;
}
}
