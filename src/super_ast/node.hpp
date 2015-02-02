#pragma once

namespace super_ast
{
	class Node
	{
	public:
		// This types could be used to analyze and classify different nodes in groups
		enum NodeType {
			UNKNOWN,
			BLOCK,
			DECLARATION,
			PARAMETER,
			LOOP,
			FOR_LOOP,
			WHILE_LOOP,
			EXPRESSION,
			ASSIGNATION,
			CONDITIONAL
			// ...
		};

		Node();
		~Node();

		// Polymorphism
		virtual bool is(NodeType type) const;
	};
}
