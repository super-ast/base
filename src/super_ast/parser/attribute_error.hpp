#pragma once
#include <sstream>
#include "parse_error.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace super_ast {
class AttributeError : public ParseError {
public:
  AttributeError(const std::string& attribute_name, const std::string& error,
      const rapidjson::Value& node) {
    std::stringstream ss;
    ss << "'" << attribute_name << "' " << error << " in object:" << std::endl;

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    node.Accept(writer);
    ss << buffer.GetString();

    error_ = ss.str();
  }

  virtual const char* what() const throw() {
    return error_.c_str();
  }

private:
  std::string error_;
};
}