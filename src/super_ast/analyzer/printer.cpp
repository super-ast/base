#include "super_ast.hpp"

int main() {
  const super_ast::Block* ast = super_ast::Parse(std::cin);

  ast->Print();

  delete ast;
  return 0;
}
