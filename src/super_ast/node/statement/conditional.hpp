#pragma once

#include "../block.hpp"
#include "expression.hpp"
#include <string>

namespace super_ast {
class Conditional : public Statement {
    Expression* condition_;
    Block* then_block_;
    Block* else_block_;

public:
    Conditional(Expression* condition, Block* then_block);

    Conditional(Expression* condition, Block* then_block, Block* else_block);

    ~Conditional();

    const Expression& condition() const;

    const Block& then_block() const;

    bool has_else_block() const;

    const Block& else_block() const;
};
}
