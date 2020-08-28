#include <iostream>

#include <readline/readline.h>
#include <readline/history.h>

#include "Readline.h"

void ReadLine::setup() {
    rl_catch_signals = true;
    rl_set_signals();
}

void ReadLine::reset() {
    std::cout << std::endl;
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

const ReadLine::Response ReadLine::read(const std::string& prompt) {
    char *buffer = readline(prompt.c_str());

    auto status = buffer ? ReadLine::Status::OK : ReadLine::Status::QUIT;
    ReadLine::Response response { status, buffer ? buffer : "" };

    free(buffer);

    return response;
}

void ReadLine::addHistory(const std::string& line) {
    add_history(line.c_str());
}
