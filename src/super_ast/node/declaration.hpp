#pragma once

#include "../node.hpp"
#include <string>

namespace super_ast {
class Declaration : public Node {
public:
    enum DataType {
        VOID,
        BOOLEAN,
        INTEGER,
        DOUBLE,
        STRING,
        COLLECTION    // vectors, lists...
        // ...
    };

    const std::string& name() const;

private:
    std::string name_;
};
}
