#include <string>
#include <unordered_map>

#include "core_functions.h"

// TODO -- consider using Boost.Bimap instead which supports lookup in either direction
static std::unordered_map<Type, const std::string> sTypeNames {
    { Type::Nil, "Nil" },
    { Type::T, "T" },
    { Type::Symbol, "Symbol" },
    { Type::Pair , "Pair" },
    { Type::Int64, "Int64" }
};

static const std::string sUnknownTypeName = "Unknown";

const std::string& typeName(Type t) {
    if (sTypeNames.contains(t)) {
        return sTypeNames[t];
    } else {
        return sUnknownTypeName;
    }
}

Ref typeSymbol(Type t) {
    return Symbol::make(typeName(t));
}

Type objectType(Ref object) {
    return object ? object->type_ : Type::Nil;
}
