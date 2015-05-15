#include "statement.hpp"

namespace super_ast {
Statement::Statement() : line_(0) {

}

unsigned int Statement::line() const {
  return line_;
}

unsigned int Statement::column() const {
  return column_;
}

void Statement::set_line(unsigned int line) {
  line_ = line;
}


void Statement::set_column(unsigned int column) {
  column_ = column;
}
}
