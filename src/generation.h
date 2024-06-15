#pragma once

#include <sstream>
#include "parser.h"

class Generation {
public:
    inline explicit Generation(NodeExit root)
            : m_root(std::move(root)) {
    }

    [[nodiscard]] std::string generate() const {
        std::stringstream output;
        output << "global _start\n";
        output << "_start:\n";
        output << "    mov rax, 60\n";  // syscall number for exit
        output << "    mov rdi, " << m_root.expr.int_lit.value.value() << "\n";  // exit code
        output << "    syscall\n";
        return output.str();
    }

private:
    const NodeExit m_root;
};
