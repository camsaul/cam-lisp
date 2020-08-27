#include <iostream>

#include "Function.h"
#include "String.h"

String::String(const std::string& s): Object { type::STRING }, s_(s) {}

String::~String() {
    std::cout << "Delete String " << (void*)this << std::endl;
}

ObjectPtr MakeString(const std::string& s) {
    return std::make_shared<String>(s);
}

void String::Initialize() {
    Method::Print.AddMethod(type::STRING, [](_Args& args) -> ObjectPtr {
        auto _this = (String *)args[0].get();
        std::cout << _this->Value() << std::endl;
        return NULL;
    });

    // Method::Destroy.AddMethod(type::STRING, [](_Args& args) -> ObjectPtr {
    //     ObjectPtr _this = args[0];
    //     if (_this->data) {
    //         std::string* data = (std::string *)_this->data;
    //         std::cout << "Delete std::string " << (size_t)_this << std::endl;
    //         delete data;
    //         _this->data = NULL;
    //     }
    //     return NULL;
    // });
}
