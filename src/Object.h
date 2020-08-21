#pragma once

#include <iostream>
#include <memory>

typedef std::string Type;

namespace type {
    static const Type TYPE = "type";
}

struct Object {
    const Type& type;
    void* data = NULL;

    ~Object();

    friend std::ostream& operator<<(std::ostream& os, const Object& rhs);
};

typedef std::shared_ptr<Object> ObjectPtr;
