#pragma once

#include <iostream>

namespace PrintOption {
    enum Options : unsigned {
        None            = 0b0000, // 0
        MachineReadable = 0b0001, // 1
        Pretty          = 0b0010, // 2
        PrintTypeTag    = 0b0100, // 4
        PrintMetadata   = 0b1000  // 8
    };

    // TODO -- use a dynamic var instead.
    Options options();
    Options set(Options opts);
    inline Options set(unsigned opts) { return set(static_cast<Options>(opts)); }

    inline Options enable(PrintOption::Options opts) {
        return set(options() | opts);
    }

    inline Options disable(PrintOption::Options opts) {
        return set(options() ^ opts);
    }
}

inline std::ostream& operator<<(std::ostream& os, PrintOption::Options opts) {
    PrintOption::set(opts);
    return os;
}
