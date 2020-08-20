#include <iostream>

// #include "../vendor/cpp-readline/src/Console.hpp"

#include "Bootstrap.h"
#include "Function.h"
#include "Object.h"
#include "Type.h"
#include "Readline.h"
#include "String.h"

int main() {
    Bootstrap();

    std::string input;

    std::cout << type::STRING << std::endl;

    {
        Object MY_OBJECT = String("Neat!");
        std::cout << MY_OBJECT << std::endl;
    }

    while (true) {
        auto response = ReadLine::Read(">");

        if (response.status != ReadLine::Status::OK) break;

        ReadLine::AddHistory(response.line);

        std::cout << response.line << std::endl;
    }

    return 0;
}
