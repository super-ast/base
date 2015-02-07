#include "node.hpp"
#include <iostream>

super_ast::Node::Node() {

}

super_ast::Node::~Node() {

}

bool super_ast::Node::is(super_ast::Node::NodeType type) const {
    return super_ast::Node::UNKNOWN == type;
}

void super_ast::Node::Print() const {
    Print(0);
}

void super_ast::Node::Print(unsigned int depth) const {
    std::cout << std::string(depth * 2, ' ') << Representation() << std::endl;
    PrintChildren(depth + 1);
}

void super_ast::Node::PrintChildren(unsigned int depth) const {
    // No children
}

std::string super_ast::Node::Representation() const {
    return "Unknown";
}
