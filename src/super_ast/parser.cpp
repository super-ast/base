#include "parser.hpp"
#include "rapidjson/document.h"
#include "parser/stream_wrapper.hpp"
#include "parser/attribute_error.hpp"

namespace super_ast {
namespace {
// Headers to enable recursion
Block* ParseBlock(const rapidjson::Value& block_def);
Statement* ParseStatement(const rapidjson::Value& statement_def);

Block* ParseBlock(const rapidjson::Value& block_def) {
  Block* block = new Block();

  if(block_def.HasMember("statements")) {
    const rapidjson::Value& statements = block_def["statements"];

    if(!statements.IsArray())
      throw AttributeError("statements", "is not an array", block_def);

    for(unsigned int i = 0; i < statements.Size(); ++i) {
      block->AppendStatement(ParseStatement(statements[i]));
    }
  }

  return block;
}

Statement* ParseStatement(const rapidjson::Value& statement_def) {
  Statement* statement = new Statement();

  // TODO: Check type attribute and delegate parsing

  return statement;
}
}

const Block* Parse(std::istream& stream) {
  rapidjson::Document d;

  StreamWrapper s(stream);
  d.ParseStream(s);

  try {
    return ParseBlock(d);
  } catch(AttributeError& error) {
    std::cerr << error.what() << std::endl;
    std::exit(1);
  }
}
}
