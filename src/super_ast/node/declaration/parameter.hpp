#pragma once

#include "../declaration.hpp"

namespace super_ast
{
    class Parameter : public Declaration
    {
        DataType parameter_type_;

    public:
        DataType(const std::string& name, DataType parameter_type);
        ~DataType();
        
        DataType parameter_type() const;
    };
}
