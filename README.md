# Compiling an analyzer
  1. Clone this repository: `git clone https://bitbucket.org/hecrj/super_ast.git`
  2. Change the current working directory to the repository location: `cd super_ast`
  3. Initialize and download the repository submodules: `git submodule update --init`
  4. Create a `build` directory to keep things clean: `mkdir build`
  5. Change the current working directory to the `build` directory: `cd build`
  6. Run `cmake ..` to generate a `Makefile` of the analyzers.
  7. Run `make [analyzer]` where `[analyzer]` is the analyzer name to generate its executable.
     Run `make` or `make all` to build all the analyzers.

# Current analyzers
## grapher
Reads a `super_ast` in `JSON` format and prints a graph in `dot` format that represents the `super_ast`.

```bash
./grapher < examples/fibonacci.json | dot -Tps -o fibonacci.ps
```

## printer
Reads a `super_ast` in `JSON` format and prints the structure of the resulting `super_ast`.

### Examples
#### Hello world
The input can be found in `examples/hello_world.json`.

```
0    BLOCK
1      FUNCTION int main
3        BLOCK
4          FUNCTION_CALL print
5            +
6              Hello world!
7              \n
8          RETURN
9            INT(0)
```

#### Fibonacci
The input can be found in `examples/fibonacci.json`.

```
0    BLOCK
1      FUNCTION int fibonacci
3        VAR int n
5        BLOCK
6          CONDITIONAL
7            <=
8              ID(n)
9              INT(1)
10           BLOCK
11             RETURN
12               ID(n)
13         RETURN
14           +
15             FUNCTION_CALL fibonacci
16               -
17                 ID(n)
18                 INT(1)
19             FUNCTION_CALL fibonacci
20               -
21                 ID(n)
22                 INT(2)
```

#### Structs
The input can be found in `examples/structs.json`.

```
0    BLOCK
1      STRUCT User
2        VAR string name
4        VAR string password
6      VAR struct[User] user
8      =
9        []
10         ID(user)
11         name
12       Rene
13     =
14       []
15         ID(user)
16         password
17       ithinkthereforeiexist
```

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
`line`*      | `int`

### Conditional
Attribute    | Value
-------------|-------------
`type`       | `"conditional"`
`condition`  | `Expression`
`then`       | `Block`
`else`*      | `Block`

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
`type`       | `string(+, -, *, %, =, <, >, ==, <=, >=, or, and, [], .)`
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

#### Not Supported
Attribute     | Value
--------------|-------------
`type`        | `string(warning, error)`
`value`       | `string`
`description`*| `string`

#### Function call
Attribute    | Value
-------------|-------------
`type`       | `"function-call"`
`name`       | `string`
`arguments`  | `array[Expression]`

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
`is_reference`*| `bool` (default: `false`)
`is_constant`* | `bool` (default: `false`)
`init`*        | `Expression` (default: `null`)

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
