#pragma once

#include <string>

namespace super_ast {
class Node {
public:
  // This types could be used to analyze and classify different nodes in groups
  enum NodeType {
    UNKNOWN,
    BLOCK,

    // - Statements
    CONDITIONAL,

    // -- Declarations
    DECLARATION,
    FUNCTION_DECLARATION,
    VARIABLE_DECLARATION,
    PARAMETER_DECLARATION,
    STRUCT_DECLARATION,

    // -- Loops
    LOOP,
    FOR_LOOP,
    WHILE_LOOP,

    // -- Expressions
    EXPRESSION,
    ASSIGNMENT,

    // --- Binary operators
    ADDITION,
    SUBTRACTION,
    PRODUCT,

    // --- Function calls
    FUNCTION_CALL,
    INPUT,
    PRINT,

    // --- Atoms
    ATOM,
    BOOLEAN,
    INTEGER,
    DOUBLE,
    STRING,
    // ...
  };

  Node();

  ~Node();

  virtual bool is(NodeType type) const;

  virtual std::string Representation() const;

  void Print() const;
  void Print(unsigned int depth) const;

protected:
  virtual void PrintChildren(unsigned int depth) const;
};
}
