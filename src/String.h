#include "Object.h"
#include "Type.h"

namespace type {
    static const Type STRING { "String" };
}

Object String(const std::string& s);
