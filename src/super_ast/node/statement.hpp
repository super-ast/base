#pragma once

#include "../node.hpp"

namespace super_ast {
class Statement : public Node {
public:
  Statement();

  int line() const;
  int column() const;

  void set_line(unsigned int line);
  void set_column(unsigned int column);

private:
  int line_;
  int column_;
};
}
