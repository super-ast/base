/**
* Library include file
*/

// Node abstraction
#include "super_ast/type.hpp"
#include "super_ast/node_map.hpp"
#include "super_ast/node.hpp"

// Main nodes
#include "super_ast/node/type_reference.hpp"
#include "super_ast/node/block.hpp"

// - Statements
#include "super_ast/node/statement.hpp"
#include "super_ast/node/statement/conditional.hpp"
#include "super_ast/node/statement/return.hpp"

// -- Loops
#include "super_ast/node/statement/loop.hpp"
#include "super_ast/node/statement/loop/for.hpp"
#include "super_ast/node/statement/loop/while.hpp"

// -- Expressions
#include "super_ast/node/statement/expression.hpp"
#include "super_ast/node/statement/expression/unary_operator.hpp"
#include "super_ast/node/statement/expression/binary_operator.hpp"

// --- Declarations
#include "super_ast/node/statement/expression/declaration.hpp"
#include "super_ast/node/statement/expression/declaration/function_declaration.hpp"
#include "super_ast/node/statement/expression/declaration/struct_declaration.hpp"
#include "super_ast/node/statement/expression/declaration/variable_declaration.hpp"

// --- Atoms
#include "super_ast/node/statement/expression/atom.hpp"
#include "super_ast/node/statement/expression/atom/function_call.hpp"
#include "super_ast/node/statement/expression/atom/identifier.hpp"
#include "super_ast/node/statement/expression/atom/boolean.hpp"
#include "super_ast/node/statement/expression/atom/integer.hpp"
#include "super_ast/node/statement/expression/atom/double.hpp"
#include "super_ast/node/statement/expression/atom/string.hpp"
#include "super_ast/node/statement/expression/atom/tuple.hpp"
#include "super_ast/node/statement/expression/atom/not_supported.hpp"

// Parser
#include "super_ast/parser.hpp"
