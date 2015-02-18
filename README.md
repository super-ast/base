## Compiling an analyzer
  1. Download or clone this repository: `git clone https://hecrj@bitbucket.org/hecrj/super_ast.git`
  2. Change the current working directory to the repository location: `cd super_ast`
  3. Create a `build` directory to contains the binary files: `mkdir build`
  4. Change the current working directory to the `build` directory: `cd build`
  5. Run `cmake ..` to generate a `Makefile` of the analyzers.
  6. Run `make [analyzer]` where `[analyzer]` is the analyzer name to generate its executable.
     Run `make` or `make all` to build all the analyzers.

## Current analyzers

### Printer
Reads a `super_ast` in `JSON` format and prints the structure of the resulting `super_ast`.

Using [Google C++ Style Guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.html)
