#include <iostream>

#include "String.h"

String::String(const std::string& str) :
    Object(type::STRING), s(str)
{}

String::~String() {
    std::cout << "Destroying String" << std::endl;
}
