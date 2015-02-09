#pragma once
#include <sstream>
#include "parse_error.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace super_ast {
class ValueError : public ParseError {
public:
  ValueError(const rapidjson::Value& node) {
    std::stringstream ss;
    ss << "Invalid value:" << std::endl;

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