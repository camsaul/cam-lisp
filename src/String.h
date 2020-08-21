#pragma once

#include <string>

#include "Object.h"

namespace type {
    static const Type STRING = "string";
}

class String : public Object {
public:
    const std::string s;

    String(const std::string& s);

    virtual ~String();
};
