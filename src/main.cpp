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

/// returns true if the signal was "handled" and we should continue running; otherwise false meaning we should exit.
bool handleCtrlC() {
    if (!incomplete) {
        std::cout << std::endl << "Bye!" << std::endl;
        return false;
    }

    std::cout << std::endl << "Ctrl-C" << std::endl;
    incomplete = false;
    buffer = "";
    return true;
}

void eval(Ref& object) {
    std::cout << PrintOption::ANSIColor::Green
              << object
              << std::endl;
}

std::string prompt() {
    return incomplete
        ? (PrintOption::ANSIColor::Yellow + ">> " + PrintOption::ANSIColor::Reset)
        : (PrintOption::ANSIColor::Green + "> " + PrintOption::ANSIColor::Reset);
}

void parseBuffer() {
    auto itr = buffer.cbegin();
    auto end = buffer.cend();
    auto result = Reader::read(itr, end);

    buffer.erase(buffer.cbegin(), itr);

    incomplete = result.status == Reader::Status::Incomplete;

    for (const auto& rawForm : result.rawForms) {
        ReadLine::addHistory(rawForm);
    }

    // TODO -- handle Reader::Status::Error

    for (auto& object : result.objects) {
        eval(object);
    }
}

void mainLoop() {
    while (true) {
        // normally sigsetjmp returns 0; if handleSignal() is called we'll jump to here and sigsetjmp() will return 1
        // (passed in handleSignal). In that case do Ctrl-C handling and restart the main loop
        if (sigsetjmp(ctrlcBuf, 1) != 0) {
            // If Ctrl-C happened while the current form was incomplete, just clear out the buffer and restart the
            // loop. If not in incomplete-mode break out of the loop so the program will exit.
            if (!handleCtrlC()) break;
            continue;
        }

        std::cout << "BUFFER = [" << buffer << ']' << std::endl;

        auto response = ReadLine::read(prompt());
        if (response.status != ReadLine::Status::OK) break;

        buffer += response.line;

        parseBuffer();
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

    std::cout << PrintOption::ANSIColor::Yellow
              << "*print-type-info*"
              << PrintOption::ANSIColor::Reset
              << PrintOption::enable(PrintOption::PrintTypeTag)
              << std::endl
              << pair
              << std::endl;

    mainLoop();

    return 0;
}
