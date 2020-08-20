#include "String.h"

Object String(const std::string& s) {
    std::string *copy = new std::string { s };
    return Object { type::STRING, copy };
}
