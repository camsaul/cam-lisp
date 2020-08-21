#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "Object.h"

typedef const std::vector<Object*> _Args;

typedef std::function<Object*(_Args&)> _Function;

namespace type {
    static const Type FUNCTION = "function";
}

// TODO - make Function and Method Objects

typedef std::unordered_map<Type, _Function> _MethodTable;

class Method {
    _MethodTable _table = {};
 public:
    static Method Print;

    /// return the a pointer to the method for type if one exists. Otherwise NULL
    const _Function * const GetMethod(const Type& type) const;

    // Add (or replace) the method implementation for a type.
    void AddMethod(const Type& type, _Function f);

    inline Object* operator()(Object& arg) const { return (*this)(&arg); }
    Object* operator()(Object* arg) const;
    Object* operator()(_Args& args) const;
};

Object * Print(const Object& object);
