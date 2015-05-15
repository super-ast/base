#pragma once

#include "../node.hpp"

namespace super_ast {
class Statement : public Node {
public:
  Statement();

  unsigned int line() const;
  unsigned int column() const;

  void set_line(unsigned int line);
  void set_column(unsigned int column);

private:
  unsigned int line_;
  unsigned int column_;
};
}
