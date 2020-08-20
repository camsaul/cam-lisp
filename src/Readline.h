#pragma once

// Wrapper around GNU readline.

#include <iostream>

namespace ReadLine {
    enum class Status { OK, QUIT };

    struct Response {
        Status status { Status::OK };
        std::string line;
    };

    const ReadLine::Response Read(const std::string& prompt);

    void AddHistory(const std::string& line);
}
