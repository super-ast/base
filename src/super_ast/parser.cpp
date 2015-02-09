#include "rapidjson/document.h"
#include "super_ast.hpp"
#include "parser/stream_wrapper.hpp"
#include "parser/attribute_error.hpp"
#include "parser/value_error.hpp"
#include <map>
#include <string>

namespace super_ast {
namespace {
// Headers to enable recursion
Block* ParseBlock(const rapidjson::Value& block_def);
Statement* ParseStatement(const rapidjson::Value& statement_def);
FunctionDeclaration* ParseFunctionDecalaration(const rapidjson::Value& function_def);
ParameterDeclaration* ParseParameterDeclaration(const rapidjson::Value& param_def);
Declaration::DataType ParseDataType(const rapidjson::Value& object, const std::string& attr);
Expression* ParseExpression(const rapidjson::Value& function_def);

// Parser mappers
typedef Statement* (*StatementParser)(const rapidjson::Value&);
std::map<std::string, super_ast::StatementParser> statement_parsers = {
    {"function-declaration", (StatementParser) ParseFunctionDecalaration},
    // TODO: Complete
};

std::map<std::string, super_ast::Declaration::DataType> data_types = {
    {"bool", Declaration::DataType::BOOLEAN},
    {"int", Declaration::DataType::INTEGER},
    {"string", Declaration::DataType::STRING},
    // TODO: Complete
};

// Assertion utilities
void assert_has(const rapidjson::Value& value, const std::vector<std::string>& attrs) {
  for(const std::string& attr : attrs) {
    if(!value.HasMember(attr.c_str())) {
      throw AttributeError(attr, "not found", value);
    }
  }
}

void assert_string(const rapidjson::Value& value, const std::vector<std::string>& attrs) {
  assert_has(value, attrs);

  for(const std::string& attr : attrs) {
    if(!value[attr.c_str()].IsString()) {
      throw AttributeError(attr, "is not a string", value);
    }
  }
}

void assert_int(const rapidjson::Value& value, const std::vector<std::string>& attrs) {
  assert_has(value, attrs);

  for(const std::string& attr : attrs) {
    if(!value[attr.c_str()].IsInt()) {
      throw AttributeError(attr, "is not an integer", value);
    }
  }
}

void assert_array(const rapidjson::Value& value, const std::vector<std::string>& attrs) {
  assert_has(value, attrs);

  for(const std::string& attr : attrs) {
    if(!value[attr.c_str()].IsArray()) {
      throw AttributeError(attr, "is not an array", value);
    }
  }
}

void assert_object(const rapidjson::Value& value, const std::vector<std::string>& attrs) {
  assert_has(value, attrs);

  for(const std::string& attr : attrs) {
    if(!value[attr.c_str()].IsObject()) {
      throw AttributeError(attr, "is not an object", value);
    }
  }
}

// Node parsers
Block* ParseBlock(const rapidjson::Value& block_def) {
  assert_array(block_def, {"statements"});

  Block* block = new Block();
  const rapidjson::Value& statements = block_def["statements"];

  for(unsigned int i = 0; i < statements.Size(); ++i) {
    block->AppendStatement(ParseStatement(statements[i]));
  }

  return block;
}

Statement* ParseStatement(const rapidjson::Value& statement_def) {
  assert_string(statement_def, {"type"});

  Statement* statement;

  if(statement_parsers.find(statement_def["type"].GetString()) != statement_parsers.end()) {
    statement = (*statement_parsers[statement_def["type"].GetString()])(statement_def);
  } else {
    statement = ParseExpression(statement_def);
  }

  return statement;
}

FunctionDeclaration* ParseFunctionDecalaration(const rapidjson::Value& function_def) {
  assert_string(function_def, {"name"});
  assert_array(function_def, {"params"});
  assert_object(function_def, {"body"});

  std::vector<ParameterDeclaration*> params;
  const rapidjson::Value& params_def = function_def["params"];

  for(int i = 0; i < params_def.Size(); ++i) {
    params.push_back(ParseParameterDeclaration(params_def[i]));
  }

  return new FunctionDeclaration(function_def["name"].GetString(),
      ParseDataType(function_def, "return-type"), params, ParseBlock(function_def["body"]));
}

ParameterDeclaration* ParseParameterDeclaration(const rapidjson::Value& param_def) {
  assert_string(param_def, {"name"});

  return new ParameterDeclaration(param_def["name"].GetString(),
      ParseDataType(param_def, "data-type"));
}

Declaration::DataType ParseDataType(const rapidjson::Value& object, const std::string& attr) {
  assert_string(object, {attr});

  if(data_types.find(object[attr.c_str()].GetString()) == data_types.end()) {
    throw AttributeError(attr, "has an invalid value", object);
  }

  return data_types[object[attr.c_str()].GetString()];
}

Expression* ParseExpression(const rapidjson::Value& function_def) {
  return new Expression();
}
}

const Block* Parse(std::istream& stream) {
  rapidjson::Document d;

  StreamWrapper s(stream);
  d.ParseStream(s);

  try {
    return ParseBlock(d);
  } catch(ParseError& error) {
    std::cerr << error.what() << std::endl;
    std::exit(1);
  }
}
}
