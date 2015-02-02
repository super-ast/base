#pragma once

#include "../declaration.hpp"

namespace super_ast
{
    class Variable : public Declaration
    {
        DataType variable_type_;

    public:
        Variable(const std::string& name, DataType variable_type);
        ~Variable();

        DataType variable_type() const;
    };
}
