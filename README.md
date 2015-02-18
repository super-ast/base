## Compiling an analyzer
  1. Clone this repository: `git clone https://hecrj@bitbucket.org/hecrj/super_ast.git`
  2. Change the current working directory to the repository location: `cd super_ast`
  3. Initialize and download the repository submodules: `git submodule update --init`
  4. Create a `build` directory to contains the binary files: `mkdir build`
  5. Change the current working directory to the `build` directory: `cd build`
  6. Run `cmake ..` to generate a `Makefile` of the analyzers.
  7. Run `make [analyzer]` where `[analyzer]` is the analyzer name to generate its executable.
     Run `make` or `make all` to build all the analyzers.

## Current analyzers

### Printer
Reads a `super_ast` in `JSON` format and prints the structure of the resulting `super_ast`.


## Coding style
Using ideas from [Google C++ Style Guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.html)
