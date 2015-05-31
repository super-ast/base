#pragma once

namespace super_ast {
class Node;
class Block;
class Statement;
class TypeReference;

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
class Boolean;
class Integer;
class Double;
class String;
class Tuple;
class NotSupported;

class For;
class While;

class Visitor {
public:
  #define VISIT(TYPE) \
  virtual void Visit(const TYPE* node);

  VISIT(Node)
  VISIT(Block)
  VISIT(Statement)
  VISIT(TypeReference)

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
  VISIT(Boolean)
  VISIT(Integer)
  VISIT(Double)
  VISIT(String)
  VISIT(Tuple)
  VISIT(NotSupported)

  #undef VISIT
};
}
