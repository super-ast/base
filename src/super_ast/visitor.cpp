#include "super_ast.hpp"

#define DELEGATE(TYPE, PARENT) \
void Visitor::Visit(const TYPE* node, int depth) {\
  Visit((PARENT*)node, depth); \
}

namespace super_ast {
bool Visitor::PRE_ORDER = true;
bool Visitor::POST_ORDER = false;


Visitor::Visitor(bool in_pre_order) : in_pre_order_(in_pre_order) {

}

bool Visitor::in_pre_order() const {
  return in_pre_order_;
}

void Visitor::Visit(const Node* node, int depth) {

}

DELEGATE(Block, Node);
DELEGATE(Statement, Node);
DELEGATE(Type, Node);

DELEGATE(Conditional, Statement);
DELEGATE(Declaration, Statement);
DELEGATE(Expression, Statement);
DELEGATE(Loop, Statement);

DELEGATE(FunctionDeclaration, Declaration);
DELEGATE(VariableDeclaration, Declaration);

DELEGATE(Atom, Expression);
DELEGATE(BinaryOperator, Expression);
DELEGATE(UnaryOperator, Expression);

DELEGATE(For, Loop);
DELEGATE(While, Loop);

DELEGATE(FunctionCall, Atom);
DELEGATE(Identifier, Atom);
DELEGATE(Integer, Atom);
DELEGATE(String, Atom);

}
