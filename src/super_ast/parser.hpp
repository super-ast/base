#include "node/block.hpp"
#include <iostream>

namespace super_ast {
const Block* Parse(const std::string& json);

const Block* Parse(std::istream& stream);
}
