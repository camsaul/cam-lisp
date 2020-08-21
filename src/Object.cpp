#include <iostream>

#include "Function.h"
#include "Object.h"

Object::Object(const Type& t): type(t) {}

// std::ostream& operator<<(std::ostream& os, const Object& rhs) {
//     Method::Print(const_cast<Object&>(rhs));
//     return os;
// }

std::ostream& operator<<(std::ostream& os, const ObjectPtr rhs) {
    Method::Print(rhs);
    return os;
}
