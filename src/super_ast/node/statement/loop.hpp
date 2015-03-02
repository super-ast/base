#pragma once

#include "../statement.hpp"
#include "../block.hpp"

namespace super_ast {
class Loop : public Statement {
public:
  Loop(Block* body);

  ~Loop();

  const Block& body() const;

  std::string Representation() const;

protected:
  void PrintChildren(unsigned int depth) const;

private:
  Block* body_;
};
}
