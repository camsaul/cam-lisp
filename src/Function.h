#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "Object.h"

typedef const std::vector<ObjectPtr> _Args;

typedef std::function<ObjectPtr(_Args&)> _Function;

namespace type {
    static const Type FUNCTION = "function";
}

// TODO - make Function and Method Objects

typedef std::unordered_map<Type, _Function> _MethodTable;

class Method {
    _MethodTable _table = {};
 public:
    static Method Print;
    // static Method Destroy;

    /// return the a pointer to the method for type if one exists. Otherwise NULL
    const _Function* GetMethod(const Type& type) const;

    // Add (or replace) the method implementation for a type.
    void AddMethod(const Type& type, _Function f);

    ObjectPtr operator()(ObjectPtr arg) const;
    ObjectPtr operator()(_Args& args) const;
};
