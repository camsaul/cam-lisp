#pragma once

#include <iostream>
#include <memory>

typedef std::string Type;

namespace type {
    static const Type TYPE = "type";
}

class Object {
protected:
    Object(const Type& type);

public:
    const Type& type;

    virtual ~Object() = default;

    friend std::ostream& operator<<(std::ostream& os, const Object& rhs);
};

typedef std::shared_ptr<Object> ObjectPtr;
