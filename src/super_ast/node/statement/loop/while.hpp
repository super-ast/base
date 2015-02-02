#pragma once

#include "../loop.hpp"
#include "../expression.hpp"

namespace super_ast
{
	class While : public Loop
	{
		Expression* condition_;

	public:
		While(Expression* condition, Block* body);
		~While();

		const Expression* condition() const;
	};
}
