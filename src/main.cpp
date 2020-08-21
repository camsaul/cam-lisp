#include <iostream>

#include "Bootstrap.h"
#include "Function.h"
#include "Object.h"
#include "Readline.h"
#include "String.h"

int main() {
    Bootstrap::BootstrapAll();

    {
        auto my_object = MakeString("Neat!");
        std::cout << "[Print string] " << my_object << std::endl;

        auto my_object_2 = my_object;
    }

    while (true) {
        auto response = ReadLine::Read("> ");

        if (response.status != ReadLine::Status::OK) break;

        ReadLine::AddHistory(response.line);

        std::cout << response.line << std::endl;
    }

    return 0;
}
