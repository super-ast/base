#include "not_supported.hpp"

namespace super_ast {

namespace {
std::string typenames[] = {
    "WARNING",
    "ERROR"
};
}

NotSupported::NotSupported(NotSupported::TYPE type, const std::string& value, const std::string& description)
    : type_(type), value_(value), description_(description) {

}


const std::string& NotSupported::value() const {
  return value_;
}


const std::string& NotSupported::description() const {
  return description_;
}


std::string NotSupported::Representation() const {
  return typenames[type_] + "(" + value_ + ", " + description_ + ")";
}

ACCEPT_SELF_IMPL(NotSupported)
}
