#include "node/block.hpp"
#include <iostream>

namespace super_ast {
const Block* parse(const std::string& json);
const Block* parse(std::istream& stream);
}
