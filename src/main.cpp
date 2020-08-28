#include <csetjmp>
#include <csignal>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "core_functions.h"
#include "Parse.h"
#include "PrintOptions.h"
#include "Readline.h"
#include "Type.h"
#include "Util.h"

sigjmp_buf ctrlcBuf;

void handleSignal(int signal) {
    if (signal == SIGINT) siglongjmp(ctrlcBuf, 1);
}

std::string buffer;
bool incomplete = false;

void handleCtrlC() {
    if (!incomplete) {
        std::cout << std::endl << "Bye!" << std::endl;
        exit(1);
    }

    std::cout << std::endl << "Ctrl-C" << std::endl;
    incomplete = false;
    buffer = "";
}

void printResult(const Reader::Result& result) {
    switch (result.status) {
    case Reader::Status::Ok:
        std::cout << PrintOption::ANSIColor::Green
                  << result.object
                  << PrintOption::ANSIColor::Reset
                  << std::endl;
        break;
    case Reader::Status::Incomplete:
    case Reader::Status::Empty:
        break;
    case Reader::Status::Error:
        std::cout << PrintOption::ANSIColor::Red
                  << result.object
                  << PrintOption::ANSIColor::Reset
                  << std::endl;
        break;
    }
}

std::string prompt() {
    return (incomplete
            ? (PrintOption::ANSIColor::Yellow + ">> " + PrintOption::ANSIColor::Reset)
            : (PrintOption::ANSIColor::Green + "> " + PrintOption::ANSIColor::Reset))
        + buffer;
}

void mainLoop() {
    while (true) {
        // normally sigsetjmp returns 0; if handleSignal() is called we'll jump to here and sigsetjmp() will return 1
        // (passed in handleSignal). In that case do Ctrl-C handling and restart the main loop
        if (sigsetjmp(ctrlcBuf, 1) != 0) {
            handleCtrlC();
            // ReadLine::reset();
            continue;
        }

        auto response = ReadLine::read(prompt());
        if (response.status != ReadLine::Status::OK) break;

        buffer += response.line;

        auto itr = buffer.cbegin();
        auto end = buffer.cend();
        auto result = Reader::read(itr, end);

        switch (result.status) {
        case Reader::Status::Ok:
            ReadLine::addHistory(std::string(buffer.cbegin(), itr));
            buffer = { itr, buffer.cend() };
            incomplete = false;
            break;
        case Reader::Status::Incomplete:
            incomplete = true;
            break;
        case Reader::Status::Empty:
            incomplete = false;
            break;
        case Reader::Status::Error:
            incomplete = false;
            break;
        }

        printResult(result);
    }
}

int main() {
    std::signal(SIGINT, &handleSignal);

    ReadLine::setup();

    auto pair = (cons(Symbol::make("+"),
                      cons(Int64::make(10),
                           cons(cons(Int64::make(20),
                                     Symbol::make("wow")),
                                nullptr))));
    std::cout << "MY PAIR = "
              << pair
              << std::endl;

    std::cout << "[PRINT TYPE INFO] "
              << PrintOption::enable(PrintOption::PrintTypeTag)
              << std::endl
              << pair
              << std::endl;

    mainLoop();

    return 0;
}
