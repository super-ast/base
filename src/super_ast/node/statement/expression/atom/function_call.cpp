#include "function_call.hpp"
#include <sstream>

namespace super_ast {

FunctionCall::FunctionCall(const std::string& name, const std::vector<Expression*>& arguments)
    : name_(name), arguments_(arguments) {

}

const std::string& FunctionCall::name() const {
  return name_;
}

const std::vector<Expression*>& FunctionCall::arguments() const {
  return arguments_;
}

std::string FunctionCall::Representation() const {
  std::stringstream ss;
  ss << "FUNCTION_CALL " << name_;
  return ss.str();
}

void FunctionCall::AcceptChildren(Node::Visitor& visitor, bool in_preorder, int depth) const {
  for(const Expression* argument : arguments_) {
    argument->Accept(visitor, in_preorder, depth);
  }
}
}
