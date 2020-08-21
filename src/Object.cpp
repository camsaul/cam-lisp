#include <iostream>

#include "Function.h"
#include "Object.h"

Object::~Object() {
    if (Method::Destroy.GetMethod(this->type)) {
        std::cout << "Destroying " << this->type << " object " << this << std::endl;
        Method::Destroy(this);
        this->data = NULL;
    }
}

std::ostream& operator<<(std::ostream& os, const Object& rhs) {
    Method::Print(const_cast<Object&>(rhs));
    return os;
}
