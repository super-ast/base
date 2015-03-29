#include "rapidjson/document.h"
#include "super_ast.hpp"
#include "parser/stream_wrapper.hpp"
#include "parser/attribute_error.hpp"
#include "parser/value_error.hpp"
#include <map>
#include <string>

namespace super_ast {
namespace {
// ATTRIBUTE NAMES
// Node
#define TYPE_ATTR "type"

// Statement
#define LINE_ATTR "line"

// Block
#define BLOCK_STATEMENTS_ATTR "statements"

// Conditional
#define CONDITIONAL_CONDITION_ATTR  "condition"
#define CONDITIONAL_THEN_BLOCK_ATTR "then"
#define CONDITIONAL_ELSE_BLOCK_ATTR "else"

// Loop
#define LOOP_INITIALIZATION_ATTR    "init"
#define LOOP_CONDIITON_ATTR         "condition"
#define LOOP_POST_ITERATION_ATTR    "post"
#define LOOP_BLOCK_ATTR             "block"

// Unary opreator
#define UNARY_EXPRESSION_ATTR "expression"

// Binary operator
#define BINARY_LEFT_ATTR  "left"
#define BINARY_RIGHT_ATTR "right"

// Function
#define FUNCTION_NAME_ATTR        "name"
#define FUNCTION_PARAMS_ATTR      "parameters"
#define FUNCTION_ARGS_ATTR        "arguments"
#define FUNCTION_RETURN_TYPE_ATTR "return-type"
#define FUNCTION_BLOCK_ATTR       "block"

// Param
#define VARIABLE_DECL_NAME_ATTR      "name"
#define VARIABLE_DECL_TYPE_ATTR      "data-type"
#define VARIABLE_DECL_REFERENCE_ATTR "is_reference"
#define VARIABLE_DECL_INIT_ATTR      "init"

// Return
#define RETURN_EXPRESSION_ATTR "expression"

// Atom
#define ATOM_VALUE_ATTR "value"

// Type
#define TYPE_NAME_ATTR "name"

// Vector
#define VECTOR_DATA_TYPE_ATTR "data-type"


// ERROR MESSAGES
#define ERROR_NOT_FOUND     "not found"
#define ERROR_NOT_STRING    "is not a string"
#define ERROR_NOT_INTEGER   "is not an integer"
#define ERROR_NOT_BOOLEAN   "is not a boolean"
#define ERROR_NOT_ARRAY     "is not an array"
#define ERROR_NOT_OBJECT    "is not an object"
#define ERROR_INVALID_VALUE "has an invalid value"

// Headers to enable recursion
Block* ParseBlock(const rapidjson::Value& block_def);
Statement* ParseStatement(const rapidjson::Value& statement_def);
FunctionDeclaration* ParseFunctionDecalaration(const rapidjson::Value& function_def);
VariableDeclaration* ParseVariableDeclaration(const rapidjson::Value& param_def);
Type* ParseType(const rapidjson::Value& type_def);
Type* ParseVectorType(const rapidjson::Value& vector_type_def);
Type* FindTypeByName(const rapidjson::Value& type_def);
Return* ParseReturn(const rapidjson::Value& return_def);
Conditional* ParseConditional(const rapidjson::Value& conditional_def);
While* ParseWhile(const rapidjson::Value& while_def);
For* ParseFor(const rapidjson::Value& for_def);
Expression* ParseExpression(const rapidjson::Value& function_def);
Identifier* ParseIdentifier(const rapidjson::Value& identifier_def);
Integer* ParseInteger(const rapidjson::Value& integer_def);
String* ParseString(const rapidjson::Value& string_def);
FunctionCall* ParseFunctionCall(const rapidjson::Value& function_call_def);

// Parser mappers
typedef Statement* (*StatementParser)(const rapidjson::Value&);
std::map<std::string, super_ast::StatementParser> statement_parsers = {
    {"return",               (StatementParser) ParseReturn},
    {"conditional",          (StatementParser) ParseConditional},
    {"while",                (StatementParser) ParseWhile},
    {"for",                  (StatementParser) ParseFor}
};

typedef Expression* (*ExpressionParser)(const rapidjson::Value&);
std::map<std::string, super_ast::ExpressionParser> expression_parsers = {
    {"function-declaration", (ExpressionParser) ParseFunctionDecalaration},
    {"variable-declaration", (ExpressionParser) ParseVariableDeclaration}
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

std::map<std::string, UnaryOperator::Type> unary_operator_types = {
    {"not", UnaryOperator::NOT}
};

std::map<std::string, BinaryOperator::Type> binary_operator_types = {
    {"=",   BinaryOperator::ASSIGNMENT},
    {"+",   BinaryOperator::ADDITION},
    {"-",   BinaryOperator::SUBTRACTION},
    {"*",   BinaryOperator::MULTIPLICATION},
    {"/",   BinaryOperator::DIVISION},
    {"%",   BinaryOperator::MODULO},
    {"==",  BinaryOperator::EQUAL},
    {">=",  BinaryOperator::GREATER_EQUAL},
    {">",   BinaryOperator::GREATER},
    {"<=",  BinaryOperator::LESS_EQUAL},
    {"<",   BinaryOperator::LESS},
    {"or",  BinaryOperator::OR},
    {"and", BinaryOperator::AND},
    {"[]",  BinaryOperator::ELEMENT_REFERENCE}
};

typedef Atom* (*AtomParser)(const rapidjson::Value&);
std::map<std::string, AtomParser> atom_parsers = {
    {"identifier",    (AtomParser) ParseIdentifier},
    {"int",           (AtomParser) ParseInteger},
    {"string",        (AtomParser) ParseString},
    {"function-call", (AtomParser) ParseFunctionCall}
};

// Assertion utilities
void assert_has(const rapidjson::Value& value, const std::vector<std::string>& attrs) {
  for(const std::string& attr : attrs) {
    if(!value.HasMember(attr.c_str())) {
      throw AttributeError(attr, ERROR_NOT_FOUND, value);
    }
  }
}

#define ASSERT_TYPE(name, method, error) \
void assert_##name(const rapidjson::Value& value, const std::vector<std::string>& attrs) { \
  assert_has(value, attrs); \
  \
  for(const std::string& attr : attrs) { \
    if(!value[attr.c_str()].method()) { \
      throw AttributeError(attr, error, value); \
    } \
  } \
}

ASSERT_TYPE(string, IsString, ERROR_NOT_STRING);
ASSERT_TYPE(int, IsInt, ERROR_NOT_INTEGER);
ASSERT_TYPE(boolean, IsBool, ERROR_NOT_BOOLEAN);
ASSERT_TYPE(array, IsArray, ERROR_NOT_ARRAY);
ASSERT_TYPE(object, IsObject, ERROR_NOT_OBJECT);

// Sets line number of statements
void SetLine(Statement* statement, const rapidjson::Value& definition) {
  if(definition.HasMember(LINE_ATTR)) {
    assert_int(definition, {LINE_ATTR});
    statement->set_line((unsigned int) definition[LINE_ATTR].GetInt());
  }
}

// Node parsers
Block* ParseBlock(const rapidjson::Value& block_def) {
  assert_array(block_def, {BLOCK_STATEMENTS_ATTR});

  Block* block = new Block();
  const rapidjson::Value& statements = block_def[BLOCK_STATEMENTS_ATTR];

  for(unsigned int i = 0; i < statements.Size(); ++i) {
    block->AppendStatement(ParseStatement(statements[i]));
  }

  return block;
}

Statement* ParseStatement(const rapidjson::Value& statement_def) {
  assert_string(statement_def, {TYPE_ATTR});

  Statement* statement;

  if(statement_parsers.find(statement_def[TYPE_ATTR].GetString()) != statement_parsers.end()) {
    statement = (*statement_parsers[statement_def[TYPE_ATTR].GetString()])(statement_def);
  } else {
    statement = ParseExpression(statement_def);
  }

  return statement;
}

Type* ParseType(const rapidjson::Value& type_def) {
  assert_string(type_def, {TYPE_NAME_ATTR});

  std::string name = type_def[TYPE_NAME_ATTR].GetString();

  if(data_types.find(name) != data_types.end()) {
    return (*data_types[name])();
  }

  if(type_parsers.find(name) != type_parsers.end()) {
    return (*type_parsers[name])(type_def);
  }

  return FindTypeByName(type_def);
}

Type* ParseVectorType(const rapidjson::Value& type_def) {
  assert_object(type_def, {VECTOR_DATA_TYPE_ATTR});
  return Type::Vector(ParseType(type_def[VECTOR_DATA_TYPE_ATTR]));
}

Type* FindTypeByName(const rapidjson::Value& type_def) {
  // TODO: I don't know if we really need this :/
  // I'll leave it here, just in case
  throw AttributeError(TYPE_NAME_ATTR, ERROR_INVALID_VALUE, type_def);
}

Return* ParseReturn(const rapidjson::Value& return_def) {
  assert_object(return_def, {RETURN_EXPRESSION_ATTR});

  Return* return_statement = new Return(ParseExpression(return_def[RETURN_EXPRESSION_ATTR]));

  SetLine(return_statement, return_def);
  return return_statement;
}

Conditional* ParseConditional(const rapidjson::Value& conditional_def) {
  assert_object(conditional_def, {CONDITIONAL_CONDITION_ATTR, CONDITIONAL_THEN_BLOCK_ATTR});

  Block* else_block = 0;

  if(conditional_def.HasMember(CONDITIONAL_ELSE_BLOCK_ATTR)) {
    assert_object(conditional_def, {CONDITIONAL_ELSE_BLOCK_ATTR});

    else_block = ParseBlock(conditional_def[CONDITIONAL_ELSE_BLOCK_ATTR]);
  }

  Conditional* conditional = new Conditional(
      ParseExpression(conditional_def[CONDITIONAL_CONDITION_ATTR]),
      ParseBlock(conditional_def[CONDITIONAL_THEN_BLOCK_ATTR]),
      else_block
  );

  SetLine(conditional, conditional_def);
  return conditional;
}

While* ParseWhile(const rapidjson::Value& while_def) {
  assert_object(while_def, {LOOP_CONDIITON_ATTR, LOOP_BLOCK_ATTR});

  While* whilE = new While(
      ParseExpression(while_def[LOOP_CONDIITON_ATTR]),
      ParseBlock(while_def[LOOP_BLOCK_ATTR])
  );

  SetLine(whilE, while_def);
  return whilE;
}

For* ParseFor(const rapidjson::Value& for_def) {
  assert_object(for_def, {LOOP_INITIALIZATION_ATTR, LOOP_CONDIITON_ATTR, LOOP_POST_ITERATION_ATTR, LOOP_BLOCK_ATTR});

  For* foR = new For(
      ParseExpression(for_def[LOOP_INITIALIZATION_ATTR]),
      ParseExpression(for_def[LOOP_CONDIITON_ATTR]),
      ParseExpression(for_def[LOOP_POST_ITERATION_ATTR]),
      ParseBlock(for_def[LOOP_BLOCK_ATTR])
  );

  SetLine(foR, for_def);
  return foR;
}

Expression* ParseExpression(const rapidjson::Value& expr_def) {
  assert_string(expr_def, {TYPE_ATTR});

  std::string type = expr_def[TYPE_ATTR].GetString();

  if(expression_parsers.find(type) != expression_parsers.end()) {
    return expression_parsers[type](expr_def);
  }

  if(unary_operator_types.find(type) != unary_operator_types.end()) {
    assert_object(expr_def, {UNARY_EXPRESSION_ATTR});

    UnaryOperator* uny_operator = new UnaryOperator(unary_operator_types[type],
        ParseExpression(expr_def[UNARY_EXPRESSION_ATTR]));

    SetLine(uny_operator, expr_def);
    return uny_operator;
  }

  if(binary_operator_types.find(type) != binary_operator_types.end()) {
    assert_object(expr_def, {BINARY_LEFT_ATTR, BINARY_RIGHT_ATTR});
    BinaryOperator* bin_operator = new BinaryOperator(binary_operator_types[type],
        ParseExpression(expr_def[BINARY_LEFT_ATTR]),
        ParseExpression(expr_def[BINARY_RIGHT_ATTR]));

    SetLine(bin_operator, expr_def);
    return bin_operator;
  }

  if(atom_parsers.find(type) != atom_parsers.end()) {
    return (*atom_parsers[type])(expr_def);
  }

  throw AttributeError(TYPE_ATTR, ERROR_INVALID_VALUE, expr_def);
}

FunctionDeclaration* ParseFunctionDecalaration(const rapidjson::Value& function_def) {
  assert_string(function_def, {FUNCTION_NAME_ATTR});
  assert_array(function_def, {FUNCTION_PARAMS_ATTR});
  assert_object(function_def, {FUNCTION_RETURN_TYPE_ATTR, FUNCTION_BLOCK_ATTR});

  std::vector<VariableDeclaration*> params;
  const rapidjson::Value& params_def = function_def[FUNCTION_PARAMS_ATTR];

  for(int i = 0; i < params_def.Size(); ++i) {
    params.push_back(ParseVariableDeclaration(params_def[i]));
  }

  FunctionDeclaration* func_declaration = new FunctionDeclaration(
      function_def[FUNCTION_NAME_ATTR].GetString(),
      ParseType(function_def[FUNCTION_RETURN_TYPE_ATTR]),
      params,
      ParseBlock(function_def[FUNCTION_BLOCK_ATTR]));

  SetLine(func_declaration, function_def);
  return func_declaration;
}

VariableDeclaration* ParseVariableDeclaration(const rapidjson::Value& param_def) {
  assert_string(param_def, {VARIABLE_DECL_NAME_ATTR});
  assert_object(param_def, {VARIABLE_DECL_TYPE_ATTR});

  bool is_reference = false;
  Expression* value = 0;

  if(param_def.HasMember(VARIABLE_DECL_REFERENCE_ATTR)) {
    assert_boolean(param_def, {VARIABLE_DECL_REFERENCE_ATTR});

    is_reference = param_def[VARIABLE_DECL_REFERENCE_ATTR].GetBool();
  }

  if(param_def.HasMember(VARIABLE_DECL_INIT_ATTR)) {
    assert_object(param_def, {VARIABLE_DECL_INIT_ATTR});

    value = ParseExpression(param_def[VARIABLE_DECL_INIT_ATTR]);
  }

  VariableDeclaration* param_declaration = new VariableDeclaration(
      param_def[VARIABLE_DECL_NAME_ATTR].GetString(),
      ParseType(param_def[VARIABLE_DECL_TYPE_ATTR]),
      is_reference,
      value);

  SetLine(param_declaration, param_def);
  return param_declaration;
}

Identifier* ParseIdentifier(const rapidjson::Value& identifier_def) {
  assert_string(identifier_def, {ATOM_VALUE_ATTR});

  Identifier* identifier = new Identifier(identifier_def[ATOM_VALUE_ATTR].GetString());

  SetLine(identifier, identifier_def);
  return identifier;
}

Integer* ParseInteger(const rapidjson::Value& integer_def) {
  assert_int(integer_def, {ATOM_VALUE_ATTR});

  Integer* integer = new Integer(integer_def[ATOM_VALUE_ATTR].GetInt());

  SetLine(integer, integer_def);
  return integer;
}

String* ParseString(const rapidjson::Value& string_def) {
  assert_string(string_def, {ATOM_VALUE_ATTR});

  String* string = new String(string_def[ATOM_VALUE_ATTR].GetString());

  SetLine(string, string_def);
  return string;
}

FunctionCall* ParseFunctionCall(const rapidjson::Value& function_call_def) {
  assert_string(function_call_def, {FUNCTION_NAME_ATTR});
  assert_array(function_call_def, {FUNCTION_ARGS_ATTR});

  std::vector<Expression*> arguments;
  const rapidjson::Value& arguments_def = function_call_def[FUNCTION_ARGS_ATTR];

  for(int i = 0; i < arguments_def.Size(); ++i) {
    arguments.push_back(ParseExpression(arguments_def[i]));
  }

  FunctionCall* function_call = new FunctionCall(
      function_call_def[FUNCTION_NAME_ATTR].GetString(),
      arguments);

  SetLine(function_call, function_call_def);
  return function_call;
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
