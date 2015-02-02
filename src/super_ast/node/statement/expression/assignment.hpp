#pragma once

#include "../expression.hpp"
#include <string>

namespace super_ast
{
    class Assignment : public Expression
    {
        std::string assignee_;
        Expression* expression_;

    public:
        Assignment(const std::string assignee, Expression* expression);
        ~Assignment();

        const std::string& assignee() const;
        const Expression& expression() const;
        // ...
    };
}
