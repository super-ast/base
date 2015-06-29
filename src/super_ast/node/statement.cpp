#include "statement.hpp"

namespace super_ast {
Statement::Statement() : line_(-1), column_(-1) {

}

int Statement::line() const {
  return line_;
}

int Statement::column() const {
  return column_;
}

void Statement::set_line(unsigned int line) {
  line_ = line;
}


void Statement::set_column(unsigned int column) {
  column_ = column;
}
}
