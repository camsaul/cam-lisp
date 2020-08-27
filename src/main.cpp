#include <iostream>

#include "Parse.h"
#include "Readline.h"
#include "Type.h"
#include "Util.h"

int main() {
    auto pair = (cons(Symbol::make("+"),
                      cons(Int64::make(10),
                           cons(cons(Int64::make(20),
                                     Symbol::make("wow")),
                                nullptr))));
    std::cout << "MY PAIR = " << pair << std::endl;

    while (true) {
        auto response = ReadLine::Read("> ");

        if (response.status != ReadLine::Status::OK) break;

        ReadLine::AddHistory(response.line);

        try {
            auto result = Parse(response.line);
            std::cout << result << std::endl;
        } catch (const std::runtime_error& e) {
            auto _ = Color(Color::Red);
            std::cout << "ERROR: " << e.what() << std::endl;
        }
    }

    return 0;
}
