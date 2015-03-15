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

  ACCEPT_SELF
  virtual void AcceptChildren(Visitor& visitor) const;
  virtual bool HasChildren() const;

private:
  Block* body_;
};
}
