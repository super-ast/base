#include "parser.hpp"
#include "rapidjson/document.h"
#include "parser/stream_wrapper.hpp"

namespace super_ast {
const Block* parse(std::istream& stream) {
    rapidjson::Document d;

    StreamWrapper s(stream);
    d.ParseStream(s);

    Block* root = new Block();

    // Process d here

    return root;
}
}
