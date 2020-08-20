#include "Function.h"

const _Function* const Method::GetMethod(const Type& type) const {
    auto itr = this->_table.find(type);
    if (itr != this->_table.end()) {
        return &itr->second;
    }
    return NULL;
}

void Method::AddMethod(const Type& type, _Function f) {
    // std::cout << "ADD METHOD FOR " << type << std::endl;
    this->_table[type] = f;
}

void Method::Invoke(Object& object) const {
    // TODO -- error if the method does not exist
    // TODO -- type hierarchy
    // std::cout << "Invoke " << object.type << std::endl;
    const _Function& f = this->_table.at(object.type);
    Object *args[] = { &object };
    f(args);
}

Method method::PRINT {};
Method method::DESTROY {};
