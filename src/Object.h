#pragma once

#include <iostream>

#include "Type.h"

struct Object {
    const Type& type;

    void* data { NULL };

    ~Object();

    friend std::ostream& operator<<(std::ostream& os, Object& rhs);
};
