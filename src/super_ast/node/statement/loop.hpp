#pragma once

#include "../statement.hpp"
#include "../block.hpp"

namespace super_ast {
class Loop : public Statement {
public:
  Loop(Block* body);

  ~Loop();

  const Block& body() const;

private:
  Block* body_;
};
}
