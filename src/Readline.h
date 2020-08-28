#pragma once

// Wrapper around GNU readline.

#include <iostream>

namespace ReadLine {
    enum class Status { OK, QUIT };

    struct Response {
        Status status { Status::OK };
        std::string line;
    };

    /// Install readline signal handlers so it can catch signals and do cleanup as needed. Do this after installing
    /// our own signal handlers (?)
    /// See https://stackoverflow.com/a/17035073/1198455
    void setup();

    /// reset readline after a jump caused by catching a signal
    void reset();

    const ReadLine::Response read(const std::string& prompt);

    void addHistory(const std::string& line);
}
