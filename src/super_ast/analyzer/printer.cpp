#include <iostream>
#include "super_ast.hpp"

class Printer : public super_ast::Node::Visitor {
public:
  void Visit(const super_ast::Node& node, int depth) {
    std::cout << std::string(((unsigned int)depth) * 2, ' ') << node.Representation() << std::endl;
  }
};

int main() {
  const super_ast::Block* ast = super_ast::Parse(std::cin);
  Printer printer;

  ast->Accept(printer, super_ast::Node::PRE_ORDER);

  delete ast;
  return 0;
}
