#pragma once

#include "Type.h"

inline Ref cons(Ref head, Ref tail) {
    return Pair::make(head, tail);
}

// Null-safe method to get the type of an object.
Type objectType(Ref object);

const std::string& typeName(Type t);

Ref typeSymbol(Type t);
