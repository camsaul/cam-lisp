#pragma once

#include <iostream>
#include <memory>

#include "Util.h"

typedef std::string Type;

namespace type {
    static const Type TYPE = "type";
}

class Object : protected NoCopy, protected NoMove {
protected:
    Object(const Type& type);

public:
    const Type& type;

    virtual ~Object() = default;
};

typedef std::shared_ptr<Object> ObjectPtr;

std::ostream& operator<<(std::ostream& os, const ObjectPtr rhs);
