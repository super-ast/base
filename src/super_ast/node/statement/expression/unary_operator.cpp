#include "unary_operator.hpp"

namespace super_ast {
namespace {
const std::string TypeStrings[] = {
    "NOT"
};
}

UnaryOperator::UnaryOperator(UnaryOperator::Type type, Expression* expression) :
    type_(type), expression_(expression) {

}


UnaryOperator::Type UnaryOperator::type() const {
  return type_;
}


const Expression& UnaryOperator::expression() const {
  return *expression_;
}


std::string UnaryOperator::Representation() const {
  return TypeStrings[type_];
}

void UnaryOperator::PrintChildren(unsigned int depth) const {
  expression_->Print(depth);
}
}
