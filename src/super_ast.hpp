/**
* Library include file
*/

// Node abstraction
#include "super_ast/node.hpp"

// Main nodes
#include "super_ast/node/block.hpp"
#include "super_ast/node/type.hpp"

// - Statements
#include "super_ast/node/statement.hpp"
#include "super_ast/node/statement/conditional.hpp"
#include "super_ast/node/statement/return.hpp"

// -- Declarations
#include "super_ast/node/statement/declaration.hpp"
#include "super_ast/node/statement/declaration/function_declaration.hpp"
#include "super_ast/node/statement/declaration/struct_declaration.hpp"
#include "super_ast/node/statement/declaration/variable_declaration.hpp"

// -- Loops
#include "super_ast/node/statement/loop.hpp"
#include "super_ast/node/statement/loop/for.hpp"
#include "super_ast/node/statement/loop/while.hpp"

// -- Expressions
#include "super_ast/node/statement/expression.hpp"
#include "super_ast/node/statement/expression/binary_operator.hpp"

// --- Atoms
#include "super_ast/node/statement/expression/atom.hpp"
#include "super_ast/node/statement/expression/atom/function_call.hpp"
#include "super_ast/node/statement/expression/atom/identifier.hpp"
#include "super_ast/node/statement/expression/atom/integer.hpp"
#include "super_ast/node/statement/expression/atom/string.hpp"

// Parser
#include "super_ast/parser.hpp"
