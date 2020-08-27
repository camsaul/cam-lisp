#include <atomic>

#include "Print.h"

static std::atomic<PrintOption::Options> sPrintOptions = PrintOption::None;

PrintOption::Options PrintOption::options() {
    return sPrintOptions;
}

PrintOption::Options PrintOption::set(PrintOption::Options options) {
    sPrintOptions = options;
    return options;
}
