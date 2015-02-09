#include "function_declaration.hpp"

namespace super_ast {
FunctionDeclaration::FunctionDeclaration(const std::string& name, DataType return_type,
    const std::vector<ParameterDeclaration*>& parameters, Block* block) : super(name) {

}
}
