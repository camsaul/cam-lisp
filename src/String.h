#pragma once

#include <string>

#include "Object.h"

namespace type {
    static const Type STRING = "string";
}

ObjectPtr String(const std::string& s);

const std::string& StringValue(const Object& obj);

namespace Bootstrap {
    void BootstrapString();
}
