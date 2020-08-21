#include <iostream>

#include "Bootstrap.h"
#include "Function.h"
#include "String.h"

void Bootstrap() {
    Method::Print.AddMethod(type::STRING,
                            [](_Args& args) -> Object * {
                                String *_this = (String *)args[0];
                                std::cout << _this->s << std::endl;
                                return NULL;
                            });

    // method::DESTROY.AddMethod(type::STRING,
    //                           [](Object *args[]) -> Object * {
    //                               Object *_this = args[0];
    //                               // std::cout << "IN STRING DESTRUCTOR FOR " << _this << std::endl;
    //                               std::string *data = (std::string *)_this->data;
    //                               delete data;
    //                               return NULL;
    //                           });
}
