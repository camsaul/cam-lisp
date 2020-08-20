#include "Function.h"
#include "Object.h"

Object::~Object() {
    // std::cout << "IN DESTRUCTOR FOR " << this->type << std::endl;
    if (this->data && method::DESTROY.GetMethod(this->type)) {
        method::DESTROY.Invoke(*this);
    }
    this->data = NULL;
}

std::ostream& operator<<(std::ostream& os, Object& rhs) {
    method::PRINT.Invoke(rhs);
    return os;
}
