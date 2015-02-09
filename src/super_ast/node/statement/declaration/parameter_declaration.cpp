#include "parameter_declaration.hpp"

namespace super_ast {
ParameterDeclaration::ParameterDeclaration(const std::string& name, DataType parameter_type) :
    super(name), parameter_type_(parameter_type) {

}
}
