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
Statement* ParseReturn(const rapidjson::Value& return_def);
FunctionDeclaration* ParseFunctionDecalaration(const rapidjson::Value& function_def);
ParameterDeclaration* ParseParameterDeclaration(const rapidjson::Value& param_def);
Type* ParseType(const rapidjson::Value& type_def);
Type* ParseVectorType(const rapidjson::Value& vector_type_def);
Type* FindTypeByName(const rapidjson::Value& type_def);
Expression* ParseExpression(const rapidjson::Value& function_def);
Integer* ParseInteger(const rapidjson::Value& integer_def);
String* ParseString(const rapidjson::Value& string_def);
FunctionCall* ParseFunctionCall(const rapidjson::Value& function_call_def);

// Parser mappers
typedef Statement* (*StatementParser)(const rapidjson::Value&);
std::map<std::string, super_ast::StatementParser> statement_parsers = {
    {"function-declaration", (StatementParser) ParseFunctionDecalaration},
    {"return",               (StatementParser) ParseReturn}
    // TODO: Complete
};

typedef Type* (*TypeCreator)();
std::map<std::string, TypeCreator> data_types = {
    {"void",   Type::Void},
    {"bool",   Type::Boolean},
    {"int",    Type::Integer},
    {"double", Type::Double},
    {"string", Type::String}
};

typedef Type* (*TypeParser)(const rapidjson::Value&);
std::map<std::string, TypeParser> type_parsers = {
    {"vector", ParseVectorType}
};

std::map<std::string, BinaryOperator::Type> binary_operator_types = {
    {"=",  BinaryOperator::ASSIGNMENT},
    {"+",  BinaryOperator::ADDITION},
    {"-",  BinaryOperator::SUBTRACTION},
    {"*",  BinaryOperator::MULTIPLICATION},
    {"/",  BinaryOperator::DIVISION},
    {"%",  BinaryOperator::MODULO},
    {"==", BinaryOperator::EQUAL},
    {">=", BinaryOperator::GREATER_EQUAL},
    {">",  BinaryOperator::GREATER},
    {"<=", BinaryOperator::LESS_EQUAL},
    {"<",  BinaryOperator::LESS}
};

typedef Atom* (*AtomParser)(const rapidjson::Value&);
std::map<std::string, AtomParser> atom_parsers = {
    {"int",           (AtomParser) ParseInteger},
    {"string",        (AtomParser) ParseString},
    {"function-call", (AtomParser) ParseFunctionCall}
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
  assert_object(function_def, {"return-type", "body"});

  std::vector<ParameterDeclaration*> params;
  const rapidjson::Value& params_def = function_def["params"];

  for(int i = 0; i < params_def.Size(); ++i) {
    params.push_back(ParseParameterDeclaration(params_def[i]));
  }

  return new FunctionDeclaration(function_def["name"].GetString(),
      ParseType(function_def["return-type"]), params, ParseBlock(function_def["body"]));
}

ParameterDeclaration* ParseParameterDeclaration(const rapidjson::Value& param_def) {
  assert_string(param_def, {"name"});
  assert_object(param_def, {"data-type"});

  return new ParameterDeclaration(param_def["name"].GetString(),
      ParseType(param_def["data-type"]));
}

Type* ParseType(const rapidjson::Value& type_def) {
  assert_string(type_def, {"name"});

  std::string name = type_def["name"].GetString();

  if(data_types.find(name) != data_types.end()) {
    return (*data_types[name])();
  }

  if(type_parsers.find(name) != type_parsers.end()) {
    return (*type_parsers[name])(type_def);
  }

  return FindTypeByName(type_def);
}

Type* ParseVectorType(const rapidjson::Value& type_def) {
  assert_object(type_def, {"subtype"});
  return Type::Vector(ParseType(type_def["subtype"]));
}

Type* FindTypeByName(const rapidjson::Value& type_def) {
  // TODO: I don't know if we really need this :/
  // I'll leave it here, just in case
  throw AttributeError("name", "has an invalid value", type_def);
}

Statement* ParseReturn(const rapidjson::Value& return_def) {
  // TODO: Parse returns
  return new Statement();
}

Expression* ParseExpression(const rapidjson::Value& expr_def) {
  assert_string(expr_def, {"type"});

  std::string type = expr_def["type"].GetString();

  // TODO: Parse unary expressions

  if(binary_operator_types.find(type) != binary_operator_types.end()) {
    assert_object(expr_def, {"left", "right"});
    return new BinaryOperator(binary_operator_types[type],
        ParseExpression(expr_def["left"]), ParseExpression(expr_def["right"]));
  }

  if(atom_parsers.find(type) != atom_parsers.end()) {
    return (*atom_parsers[type])(expr_def);
  }

  throw AttributeError("type", "has an invalid value", expr_def);
}

Integer* ParseInteger(const rapidjson::Value& integer_def) {
  assert_int(integer_def, {"value"});

  return new Integer(integer_def["value"].GetInt());
}

String* ParseString(const rapidjson::Value& string_def) {
  assert_string(string_def, {"value"});

  return new String(string_def["value"].GetString());
}

FunctionCall* ParseFunctionCall(const rapidjson::Value& function_call_def) {
  assert_string(function_call_def, {"name"});
  assert_array(function_call_def, {"arguments"});

  std::vector<Expression*> arguments;
  const rapidjson::Value& arguments_def = function_call_def["arguments"];

  for(int i = 0; i < arguments_def.Size(); ++i) {
    arguments.push_back(ParseExpression(arguments_def[i]));
  }

  return new FunctionCall(function_call_def["name"].GetString(), arguments);
}
}

const Block* Parse(std::istream& stream) {
  rapidjson::Document d;

  StreamWrapper s(stream);
  d.ParseStream(s);

  try {
    return ParseBlock(d);
  } catch(ParseError& error) {
    std::cerr << "ERROR: " << error.what() << std::endl;
    std::exit(1);
  }
}
}
