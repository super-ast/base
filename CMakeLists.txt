cmake_minimum_required(VERSION 2.8.4)
project(super_ast)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/super_ast/parser.cpp
    src/super_ast/node.cpp

    src/super_ast/node/block.cpp
    src/super_ast/node/type.cpp

    src/super_ast/node/statement.cpp
    src/super_ast/node/statement/conditional.cpp
    src/super_ast/node/statement/return.cpp

    src/super_ast/node/statement/declaration.cpp
    src/super_ast/node/statement/declaration/function_declaration.cpp
    src/super_ast/node/statement/declaration/variable_declaration.cpp
    src/super_ast/node/statement/declaration/struct_declaration.cpp

    src/super_ast/node/statement/expression.cpp
    src/super_ast/node/statement/expression/binary_operator.cpp

    src/super_ast/node/statement/expression/atom.cpp
    src/super_ast/node/statement/expression/atom/function_call.cpp
    src/super_ast/node/statement/expression/atom/identifier.cpp
    src/super_ast/node/statement/expression/atom/integer.cpp
    src/super_ast/node/statement/expression/atom/string.cpp

    src/super_ast/node/statement/loop.cpp
    src/super_ast/node/statement/loop/for.cpp
    src/super_ast/node/statement/loop/while.cpp
)

include_directories(
    src/
    vendor/rapidjson/include
)

add_executable(printer src/super_ast/analyzer/printer.cpp ${SOURCE_FILES})
