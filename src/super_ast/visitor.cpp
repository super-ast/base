#include "super_ast.hpp"

#define DELEGATE(TYPE, PARENT) \
void Visitor::Visit(const TYPE* node) {\
  Visit((PARENT*)node); \
}

namespace super_ast {
void Visitor::Visit(const Node* node) {

}

DELEGATE(Block, Node);
DELEGATE(Statement, Node);
DELEGATE(Type, Node);

DELEGATE(Conditional, Statement);
DELEGATE(Expression, Statement);
DELEGATE(Loop, Statement);

DELEGATE(For, Loop);
DELEGATE(While, Loop);

DELEGATE(Atom, Expression);
DELEGATE(BinaryOperator, Expression);
DELEGATE(UnaryOperator, Expression);
DELEGATE(Declaration, Expression);

DELEGATE(FunctionDeclaration, Declaration);
DELEGATE(VariableDeclaration, Declaration);

DELEGATE(FunctionCall, Atom);
DELEGATE(Identifier, Atom);
DELEGATE(Boolean, Atom);
DELEGATE(Integer, Atom);
DELEGATE(Double, Atom);
DELEGATE(String, Atom);
DELEGATE(NotSupported, Atom);
}
