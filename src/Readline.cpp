#include <readline/readline.h>
#include <readline/history.h>

#include "Readline.h"

const ReadLine::Response ReadLine::Read(const std::string& prompt) {
    char *buffer = readline(prompt.c_str());

    auto status = buffer ? ReadLine::Status::OK : ReadLine::Status::QUIT;
    ReadLine::Response response { status, buffer ? buffer : "" };

    free(buffer);

    return response;
}

void ReadLine::AddHistory(const std::string& line) {
    add_history(line.c_str());
}
