#include "binary_operator.hpp"

namespace super_ast {
namespace {
const std::string TypeStrings[] = {
    "=",
    "+",
    "-",
    "*",
    "/",
    "%",
    "==",
    ">=",
    ">",
    "<=",
    "<",
    "OR",
    "AND"
};
}

BinaryOperator::BinaryOperator(BinaryOperator::Type type, Expression* left, Expression* right)
    : type_(type), left_(left), right_(right) {

}

BinaryOperator::~BinaryOperator() {
  delete left_;
  delete right_;
}

BinaryOperator::Type BinaryOperator::type() const {
  return type_;
}

const Expression& BinaryOperator::left() const {
  return *left_;
}

const Expression& BinaryOperator::right() const {
  return *right_;
}

std::string BinaryOperator::Representation() const {
  return TypeStrings[type_];
}

void BinaryOperator::PrintChildren(unsigned int depth) const {
  left_->Print(depth);
  right_->Print(depth);
}
}
