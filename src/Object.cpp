#include <iostream>

#include "Function.h"
#include "Object.h"

Object::Object(const Type& t) :
    type(t)
{};

Object::~Object() {
    std::cout << "Destroying " << this->type << " object " << *this << std::endl;
}

// Object::~Object() {
//     // std::cout << "IN DESTRUCTOR FOR " << this->type << std::endl;
//     if (this->data && method::DESTROY.GetMethod(this->type)) {
//         method::DESTROY.Invoke(*this);
//     }
//     this->data = NULL;
// }

std::ostream& operator<<(std::ostream& os, const Object& rhs) {
    Method::Print(const_cast<Object&>(rhs));
    return os;
}
