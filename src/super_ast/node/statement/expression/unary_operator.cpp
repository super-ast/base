#include "unary_operator.hpp"

namespace super_ast {
namespace {
const std::string TypeStrings[] = {
    "NOT",
    "++_",
    "_++"
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

ACCEPT_SELF_IMPL(UnaryOperator);

void UnaryOperator::AcceptChildren(Visitor& visitor) const {
  expression_->Accept(visitor);
}

bool UnaryOperator::HasChildren() const {
  return true;
}
}
