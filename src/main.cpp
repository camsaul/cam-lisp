#include <iostream>

#include "Bootstrap.h"
#include "Function.h"
#include "Parse.h"
#include "Object.h"
#include "Readline.h"
#include "String.h"
#include "Util.h"

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

        try {
            auto result = Parse(response.line);
            std::cout << response.line << std::endl;
        } catch (const std::runtime_error& e) {
            {
                auto _ = Color(Color::Red);
                std::cout << "ERROR: " << e.what() << std::endl;
            }
        }
    }

    return 0;
}
