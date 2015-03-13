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

  virtual void Visit(const Node* node, int depth);
  virtual void Visit(const Block* block, int depth);
  virtual void Visit(const Statement* statement, int depth);
  virtual void Visit(const Type* type, int depth);

  // Statements
  virtual void Visit(const Conditional* conditional, int depth);
  virtual void Visit(const Declaration* declaration, int depth);
  virtual void Visit(const Expression* expression, int depth);
  virtual void Visit(const Loop* loop, int depth);

  // Declarations
  virtual void Visit(const FunctionDeclaration* function, int depth);
  virtual void Visit(const VariableDeclaration* variable, int depth);

  // Expressions
  virtual void Visit(const Atom* atom, int depth);
  virtual void Visit(const BinaryOperator* binary_operator, int depth);
  virtual void Visit(const UnaryOperator* unary_operator, int depth);

  // Loops
  virtual void Visit(const For* for_loop, int depth);
  virtual void Visit(const While* while_loop, int depth);

  // Atoms
  virtual void Visit(const FunctionCall* function_call, int depth);
  virtual void Visit(const Identifier* identifier, int depth);
  virtual void Visit(const Integer* integer, int depth);
  virtual void Visit(const String* string, int depth);

private:
  bool in_pre_order_;
};
}
