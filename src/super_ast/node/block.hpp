#pragma once

#include "../node.hpp"
#include <vector>

namespace super_ast
{
	/**
	 * A block is a list of statements
	 */
	class Block : public Node
	{
		std::vector<Statement*> statements_;

	public:
		Block();
		~Block();

		/**
		 * Adds the given statement at the end of this block
		 */
		void AppendStatement(Statement* statement);

		
		const std::vector<Statement*>& statements() const;

		/**
		 * Returns the total number of loops in this block
		 */
		int LoopCount() const;

		/**
		 * Returns the total number of conditionals in this block
		 */
		int ConditionalCount() const;

		// More API here...
	};
}
