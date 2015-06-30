# JSON format specification
  1. Every object in `JSON` represents a node of the `super_ast`.
  2. The root node of the `super_ast` is a `Block` node.
  3. If an attribute is marked with `*` then that attribute is optional.

# Node
Attribute    | Value
-------------|-------------
`id`         | `int`

## Block
Attribute    | Value
-------------|-------------
`statements` | `array[Statement]`

## Statement
Attribute    | Value
-------------|-------------
`line*`      | `int` (starting at 1)
`column*`    | `int` (starting at 1)

### Conditional
Attribute    | Value
-------------|-------------
`type`       | `"conditional"`
`condition`  | `Expression`
`then`       | `Block`
`else*`      | `Block`

### Return
Attribute    | Value
-------------|-------------
`type`       | `"return"`
`expression` | `Expression`

### Loop
Attribute    | Value
-------------|-------------
`block`      | `Block`

#### While
Attribute    | Value
-------------|-------------
`condition`  | `Expression`

#### For
Attribute    | Value
-------------|-------------
`init`       | `Expression`
`condition`  | `Expression`
`post`       | `Expression`

### Expression
#### Unary operator
Attribute    | Value
-------------|-------------
`type`       | `string(not, neg, pos, ++_, _++, --_, _--)`
`expression` | `Expression`

#### Binary operator
Attribute    | Value
-------------|-------------
`type`       | `string(+, -, *, %, <<, >>, =, +=, -=, *=, %=, <<=, >>=, <, >, ==, <=, >=, or, and, [], .)`
`left`       | `Expression`
`right`      | `Expression`

#### Identifier
Attribute    | Value
-------------|-------------
`type`       | `"identifier"`
`value`      | `string`

#### Boolean
Attribute    | Value
-------------|-------------
`type`       | `"bool"`
`value`      | `bool`

#### Integer
Attribute    | Value
-------------|-------------
`type`       | `"int"`
`value`      | `int`

#### Double
Attribute    | Value
-------------|-------------
`type`       | `"double"`
`value`      | `double`

#### String
Attribute    | Value
-------------|-------------
`type`       | `"string"`
`value`      | `string`

#### Tuple
Attribute    | Value
-------------|-------------
`type`       | `"tuple"`
`values`     | `array[Expression]`

#### Function call
Attribute    | Value
-------------|-------------
`type`       | `"function-call"`
`name`       | `string`
`arguments`  | `array[Expression]`

#### Not Supported
Attribute     | Value
--------------|-------------
`type`        | `string(warning, error)`
`value`       | `string`
`description*`| `string`

#### Declaration
##### FunctionDeclaration
Attribute     | Value
--------------|-------------
`type`        | `"function"`
`name`        | `string`
`parameters`  | `array[VariableDeclaration]`
`return-type` | `TypeReference`
`block`       | `Block`

##### VariableDeclaration
Attribute      | Value
---------------|-------------
`type`         | `"variable-declaration"`
`name`         | `string`
`data-type`    | `TypeReference`
`is_reference*`| `bool` (default: `false`)
`is_constant*` | `bool` (default: `false`)
`init*`        | `Expression` (default: `null`)

##### StructDeclaration
Attribute      | Value
---------------|-------------
`type`         | `"struct-declaration"`
`name`         | `string`
`attributes`   | `array[VariableDeclaration]`

## TypeReference
### Simple
Attribute    | Value
-------------|-------------
`name`       | `string(void, bool, int, double, string)` or the name of a user-defined type

### Vector
Attribute    | Value
-------------|-------------
`name`       | `"vector"`
`data-type`  | `TypeReference`

### Tuple
Attribute    | Value
-------------|-------------
`name`       | `"tuple"`
`data-types` | `array[TypeReference]`

# Visitor pattern example
The `printer` analyzer shows a simple visitor that prints visited nodes properly indented:

```c++
#include <iostream>
#include <iomanip>
#include "super_ast.hpp"

class Printer : public super_ast::Visitor {
public:
  Printer() {
    depth_ = 0;
  }

  void Visit(const super_ast::Node* node) {
    std::cout << std::left << std::setw(5) << node->id() <<
        std::string(depth_ * 2, ' ') << node->Representation() << std::endl;

    depth_++;
    node->AcceptChildren(*this);
    depth_--;
  }

private:
  unsigned int depth_;
};

int main() {
  const super_ast::Block* ast = super_ast::Parse(std::cin);

  Printer printer;
  ast->Accept(printer);

  return 0;
}
```

The `super_ast` nodes accept any `Visitor` that implements the `super_ast::Visitor` abstract class.
The `Visitor` can control the order in which nodes are visited by calling the method `AcceptChildren` of the visited node.
Look at the `src/super_ast/visitor.cpp` file to understand how the `Visitor` method delegation works.

# Coding style
Using ideas from [Google C++ Style Guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.html)
