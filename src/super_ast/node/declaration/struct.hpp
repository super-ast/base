#pragma once

#include "../declaration.hpp"
#include "variable.hpp"

namespace super_ast
{
    class Struct : public Declaration
    {
        // Maybe we could use a map if we need to reference attributes by its name (?)
        std::vector<Variable*> attributes_;

    public:
        Variable(const std::string& name);
        ~Variable();

        void AddAttribute(Variable* attribute);

        const std::vector<Variable*> attributes() const;
    };
}
