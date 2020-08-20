#pragma once

#include <functional>
#include <iostream>
#include <unordered_map>

#include "Type.h"
#include "Object.h"

typedef std::function<Object *(Object *[])> _Function;

namespace type {
    static const Type FUNCTION { "function" };
}

typedef std::unordered_map<Type, _Function> _Method;

class Method {
    _Method _table;
 public:
    const _Function* const GetMethod(const Type& type) const;
    void AddMethod(const Type& type, _Function f);
    void Invoke(Object& object) const;
};

namespace method {
    extern Method INITIALIZE;
    extern Method DESTROY;
    extern Method PRINT;
}
