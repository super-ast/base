#include "statement.hpp"

namespace super_ast {
Statement::Statement() : line_(0) {

}

unsigned int Statement::line() const {
  return line_;
}

void Statement::set_line(unsigned int line) {
  line_ = line;
}
}
