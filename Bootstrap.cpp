#include <iostream>

#include "Bootstrap.h"
#include "Function.h"
#include "Type.h"
#include "String.h"

void Bootstrap() {
    method::PRINT.AddMethod(type::STRING,
                            [](Object *args[]) -> Object * {
                                Object *_this = args[0];
                                std::string *data = (std::string *)_this->data;
                                std::cout << *data << std::endl;
                                return NULL;
                            });

    method::DESTROY.AddMethod(type::STRING,
                              [](Object *args[]) -> Object * {
                                  Object *_this = args[0];
                                  // std::cout << "IN STRING DESTRUCTOR FOR " << _this << std::endl;
                                  std::string *data = (std::string *)_this->data;
                                  delete data;
                                  return NULL;
                              });
}
