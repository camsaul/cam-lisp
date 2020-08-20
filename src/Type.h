#pragma once

#include <functional>
#include <iostream>

// TODO -- A type should be an Object so it's possible to call "static" methods e.g. a method to initialize a class
class Type {
 public:
    std::string name;

    friend std::ostream& operator<<(std::ostream& os, const Type& rhs);

    bool operator==(const Type& rhs) const;
};

// TODO -- can the definition go in the .cpp file?
template<> struct std::hash<Type> {
    std::size_t operator()(const Type& type) const noexcept {
        return std::hash<std::string>{}(type.name);
    }
};
