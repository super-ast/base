#pragma once
#include "../atom.hpp"
#include <vector>

namespace super_ast {
class FunctionCall : public Atom {
public:
  FunctionCall(const std::string& name, const std::vector<Expression*>& arguments);

  const std::string& name() const;
  const std::vector<Expression*>& arguments() const;

  std::string Representation() const;

protected:
  void PrintChildren(unsigned int depth) const;

private:
  std::string name_;
  std::vector<Expression*> arguments_;
};
}
