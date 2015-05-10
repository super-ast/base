#include <iostream>
#include <iomanip>
#include "super_ast.hpp"

namespace super_ast {
class UselessConditionals : public Visitor {
public:
  UselessConditionals() {

  }

  void Visit(const super_ast::Node* node) {
    node->AcceptChildren(*this);
  }

  void Visit(const Conditional *conditional) {
    if(!conditional->has_else_block())
      return;

    const Block& then_block = conditional->then_block();
    const Block& else_block = conditional->else_block();

    if(HasReturn(then_block) and HasReturn(else_block)) {
      Report(*conditional, "Unnecessary conditional with returns");
    }
  }

  bool HasReturn(const Block& block) {
    return block.statements().size() == 1 &&
        dynamic_cast<Return*>(block.statements()[0]);
  }

  void Report(const Node& node, std::string message) {
    std::cout << std::left << std::setw(5) << node.id() << message << std::endl;
  }
};
}

int main() {
  const super_ast::Block* ast = super_ast::Parse(std::cin);

  super_ast::UselessConditionals useless_conditionals;
  ast->Accept(useless_conditionals);

  return 0;
}
