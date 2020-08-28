#include <atomic>

#include "PrintOptions.h"

static std::atomic<PrintOption::Options> sPrintOptions = PrintOption::None;

PrintOption::Options PrintOption::options() {
    return sPrintOptions;
}

PrintOption::Options PrintOption::set(PrintOption::Options options) {
    sPrintOptions = options;
    return options;
}

namespace PrintOption::ANSIColor {
    const std::string Reset   = "\033[0m";
    const std::string Red     = "\033[31m";
    const std::string Green   = "\033[32m";
    const std::string Yellow  = "\033[33m";
    const std::string Blue    = "\033[34m";
    const std::string Magenta = "\033[35m";
    const std::string Cyan    = "\033[36m";
}
