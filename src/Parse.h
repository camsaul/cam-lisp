#pragma once

#include <string>

#include "Type.h"

namespace Reader {
    enum class Status {
        /// There was nothing to read.
        Empty,
        /// An object was successfully read.
        Ok,
        /// Current form is not complete.
        Incomplete,
        Error
    };

    struct Result {
        Status status;
        Ref object;
    };

    // TODO -- use utf-8 string type...
    /// read a single object.
    Result read(std::string::const_iterator& it, const std::string::const_iterator& end);

    // TODO
    //Result Read(std::istream& is);
}
