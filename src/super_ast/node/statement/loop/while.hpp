#pragma once

#include "../loop.hpp"
#include "../expression.hpp"

namespace super_ast {
class While : public Loop {
public:
    While(Expression* condition, Block* body);

    ~While();

    const Expression& condition() const;

private:
    Expression* condition_;
};
}
