#include <iostream>
#include "super_ast.hpp"

class Printer : public super_ast::Visitor {
public:
  Printer() : super_ast::Visitor(PRE_ORDER) {

  }

  void Visit(const super_ast::Node* node, int depth) {
    std::cout << std::string(depth * 2, ' ') << node->Representation() << std::endl;
  }
};

int main() {
  const super_ast::Block* ast = super_ast::Parse(std::cin);
  Printer printer;

  ast->Accept(printer);

  delete ast;
  return 0;
}
