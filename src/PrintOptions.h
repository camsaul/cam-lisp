#pragma once

#include <iostream>

namespace PrintOption {
    enum Options : unsigned {
        None            = 0b00000000, // 0
        MachineReadable = 0b00000001, // 1
        Pretty          = 0b00000010, // 2
        PrintTypeTag    = 0b00000100, // 4
        PrintMetadata   = 0b00001000  // 8
        /// TODO Whether to print lists in dotted pair form only e.g. (a . (b . (c . nil))) instead of (a b c)
        // NoLists         = 0b00010000  // 16
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

    namespace ANSIColor {
        extern const std::string Reset;
        extern const std::string Red;
        extern const std::string Green;
        extern const std::string Yellow;
        extern const std::string Blue;
        extern const std::string Magenta;
        extern const std::string Cyan;
    }
}

inline std::ostream& operator<<(std::ostream& os, PrintOption::Options opts) {
    PrintOption::set(opts);
    return os;
}
