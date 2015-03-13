#pragma once

namespace super_ast {
class Node;
class Block;
class Statement;
class Type;

class Conditional;
class Declaration;
class Expression;
class Loop;

class FunctionDeclaration;
class VariableDeclaration;
class Atom;
class BinaryOperator;
class UnaryOperator;

class FunctionCall;
class Identifier;
class Integer;
class String;

class For;
class While;

class Visitor {
public:
  static bool PRE_ORDER;
  static bool POST_ORDER;

  Visitor(bool in_pre_order);

  bool in_pre_order() const;

  #define VISIT(TYPE) \
  virtual void Visit(const TYPE* node, int depth);

  VISIT(Node)
  VISIT(Block)
  VISIT(Statement)
  VISIT(Type)

  VISIT(Conditional)
  VISIT(Declaration)
  VISIT(Expression)
  VISIT(Loop)

  VISIT(FunctionDeclaration)
  VISIT(VariableDeclaration)

  VISIT(Atom)
  VISIT(BinaryOperator)
  VISIT(UnaryOperator)

  VISIT(For)
  VISIT(While)

  VISIT(FunctionCall)
  VISIT(Identifier)
  VISIT(Integer)
  VISIT(String)

  #undef VISIT

private:
  bool in_pre_order_;
};
}
