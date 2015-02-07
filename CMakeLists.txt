cmake_minimum_required(VERSION 2.8.4)
project(super_ast)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/super_ast/node.cpp
    src/super_ast/parser.cpp

    src/super_ast/node/declaration/function.cpp
    src/super_ast/node/declaration/parameter.cpp
    src/super_ast/node/declaration/struct.cpp
    src/super_ast/node/declaration/variable.cpp
    src/super_ast/node/statement/expression/assignment.cpp
    src/super_ast/node/statement/loop/for.cpp
    src/super_ast/node/statement/loop/while.cpp
    src/super_ast/node/statement/conditional.cpp
    src/super_ast/node/statement/expression.cpp
    src/super_ast/node/statement/loop.cpp
    src/super_ast/node/block.cpp
    src/super_ast/node/declaration.cpp
    src/super_ast/node/statement.cpp
)

include_directories(
    src/
    vendor/rapidjson/include
)

add_executable(printer src/super_ast/analyzer/printer.cpp ${SOURCE_FILES})
