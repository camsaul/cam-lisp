#include <iostream>

#include "Function.h"
#include "String.h"

ObjectPtr String(const std::string& s) {
    return ObjectPtr(new Object { type::STRING,  new std::string { s } });
}

const std::string& StringValue(const Object& obj) {
    auto data = (std::string *)obj.data;
    if (!data) throw std::logic_error { "String " + std::to_string((size_t)&obj) + " has already been deleted!" };
    return *data;
}

void Bootstrap::BootstrapString() {
    Method::Print.AddMethod(type::STRING, [](_Args& args) -> Object * {
        std::cout << StringValue(*(args[0])) << std::endl;
        return NULL;
    });

    Method::Destroy.AddMethod(type::STRING, [](_Args& args) -> Object * {
        Object* _this = args[0];
        if (_this->data) {
            std::string* data = (std::string *)_this->data;
            std::cout << "Delete std::string " << (size_t)_this << std::endl;
            delete data;
            _this->data = NULL;
        }
        return NULL;
    });
}
