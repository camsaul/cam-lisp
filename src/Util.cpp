#include <iostream>

#include "Util.h"

const std::string Color::Reset = "\033[0m";
const std::string Color::Red   = "\033[31m";
const std::string Color::Green = "\033[32m";

Color::Color(const std::string& color) {
    std::cout << color;
}

Color::~Color() {
    std::cout << Color::Reset;
}

// void WithColor(const std::string& color, std::function<()> f) {
//     f();
// }
