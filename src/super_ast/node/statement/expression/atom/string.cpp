#include "string.hpp"
#include <sstream>

namespace super_ast {
String::String(const std::string& value) : value_(value) {

}

const std::string& String::value() const {
  return value_;
}

std::string String::Representation() const {
  return Escape(value_);
}

std::string String::Escape(const std::string& str) {
  std::stringstream ss;

  for(int i = 0; i < str.size(); ++i) {
    char c = str[i];

    if(isprint(c)) {
      ss << c;
    } else {
      switch(c) {
        case '\a':  ss << "\\a"; break;
        case '\b':  ss << "\\b"; break;
        case '\f':  ss << "\\f"; break;
        case '\n':  ss << "\\n"; break;
        case '\r':  ss << "\\r"; break;
        case '\t':  ss << "\\t"; break;
        case '\v':  ss << "\\v"; break;
        case '\\':  ss << "\\\\"; break;
        case '\'':  ss << "\\'"; break;
        case '\"':  ss << "\\\""; break;
        case '\?':  ss << "\\\?"; break;
        default:    break;
      }
    }
  }

  return ss.str();
}
}
