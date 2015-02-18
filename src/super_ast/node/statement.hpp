#pragma once

#include "../node.hpp"

namespace super_ast {
class Statement : public Node {
public:
  Statement();

  unsigned int line() const;

  void set_line(unsigned int line);

private:
  unsigned int line_;
};
}
