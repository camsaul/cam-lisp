#pragma once

#include <string>
#include <vector>

#include "Type.h"

namespace Reader {
    enum class Status {
        /// There was nothing to read.
        Empty,
        /// One or more objects was read successfully.
        Ok,
        /// Current form is not complete.
        Incomplete,
        Error
    };

    struct Result {
        Status status;
        std::vector<std::string> rawForms;
        std::vector<Ref> objects;
    };

    // TODO -- use utf-8 string type...
    /// read a single object.
    Result read(std::string::const_iterator& it, const std::string::const_iterator& end);

    // TODO
    //Result Read(std::istream& is);
}
