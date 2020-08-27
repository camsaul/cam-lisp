#include <exception>

#include "Function.h"

// Method Method::Destroy {};
Method Method::Print {};

const _Function* Method::GetMethod(const Type& type) const {
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

ObjectPtr Method::operator()(ObjectPtr arg) const {
    _Args args { arg };
    return (*this)(args);
}

ObjectPtr Method::operator()(_Args& args) const {
    if (args.size() == 0) throw std::runtime_error { "Method invoked with zero args" };

    auto firstArg = args[0];

    if (!firstArg) throw std::runtime_error { "Method invoked with nil first args" };

    // TODO -- type hierarchy

    const auto& f = this->_table.at(firstArg->type);
    return f(args);
}
