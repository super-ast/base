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

ACCEPT_SELF_IMPL(FunctionCall)

void FunctionCall::AcceptChildren(Visitor& visitor) const {
  for(const Expression* argument : arguments_) {
    argument->Accept(visitor);
  }
}

bool FunctionCall::HasChildren() const {
  return true;
}
}
