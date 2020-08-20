#include <iostream>

#include "Bootstrap.h"
#include "Function.h"
#include "Object.h"
#include "Type.h"
#include "String.h"

int main() {
    Bootstrap();

    std::string input;

    std::cout << type::STRING << std::endl;

    {
        Object MY_OBJECT = String("Neat!");
        std::cout << MY_OBJECT << std::endl;
    }

    std::cout << "> ";
    while (std::getline(std::cin, input)) {
        std::cout << input << std::endl;
        std::cout << "> ";
    }
    return 0;
}
