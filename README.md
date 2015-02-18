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
## printer
Reads a `super_ast` in `JSON` format and prints the structure of the resulting `super_ast`.


# JSON format specification
  1. Every object in `JSON` represents a node of the `super_ast`.
  2. The root node of the `super_ast` is a `Block` node.
  3. If an attribute is marked with `*` then that attribute is optional.

## Block
Attribute    | Value
-------------|-------------
statements   | `array[Statement]`

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

### Expression
#### Binary operator
Attribute    | Value
-------------|-------------
`type`       | `string` matching `+|-|*|/|%|(=|<|>)=?`
`left`       | `Expression`
`right`      | `Expression`

#### Identifier
Attribute    | Value
-------------|-------------
`type`       | `"identifier"`
`value`      | `string`

#### Integer
Attribute    | Value
-------------|-------------
`type`       | `"int"`
`value`      | `int`

#### String
Attribute    | Value
-------------|-------------
`type`       | `"string"`
`value`      | `string`

#### Function call
Attribute    | Value
-------------|-------------
`type`       | `"function-call"`
`name`       | `string`
`arguments`  | `array[Expression]`

# Coding style
Using ideas from [Google C++ Style Guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.html)
