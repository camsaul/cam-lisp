#pragma once

#include <string>

#include "Object.h"

namespace type {
    static const Type STRING = "string";
}

class String : public Object {
private:
    const std::string& s_;
public:
    static void Initialize();

    // TODO -- make make this private and give std::make_shared friend access to it
    String(const std::string& s);
    virtual ~String();

    inline const std::string& Value() const { return this->s_; }
};

ObjectPtr MakeString(const std::string& s);
