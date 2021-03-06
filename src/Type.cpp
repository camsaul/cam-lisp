#include <bits/stdint-intn.h>

#include "core_functions.h"
#include "PrintOptions.h"
#include "Type.h"

Object::Object(const Type& t):
    type_(t)
{}

bool Object::isEqual(const Object& rhs) const {
    return this->isIdentical(rhs);
}

std::ostream& operator<<(std::ostream& os, Ref object) {
    if (PrintOption::options() & PrintOption::PrintTypeTag) {
        // prevent recursive type info printing.
        os << PrintOption::disable(PrintOption::PrintTypeTag)
           << PrintOption::ANSIColor::Magenta
           << '^' << typeName(objectType(object))
           << PrintOption::ANSIColor::Reset << ' '
           << PrintOption::enable(PrintOption::PrintTypeTag);
    }

    if (object) {
        object->print(os);
    } else {
        os << "nil";
    };

    return os;
}

Symbol::Symbol(const std::string& value):
    Object { Type::Symbol },
    value_(value)
{}

void Symbol::print(std::ostream& os) const {
    os << this->value_;
}

Pair::Pair():
    Object { Type::Pair },
    head_(nullptr),
    tail_(nullptr)
{}

Pair::Pair(Ref head, Ref tail):
    Object { Type::Pair },
    head_(head),
    tail_(tail)
{}

Int64::Int64():
    Object { Type::Int64 },
    value_(0)
{}

Int64::Int64(int64_t value):
    Object { Type::Int64 },
    value_(value)
{}

void Int64::print(std::ostream& os) const {
    os << this->value_;
}

bool Int64::isEqual(const Object& rhs) const {
    return (this->type_ == rhs.type_)
        && this->value_ == ((Int64&)rhs).value_;
}

void printPair(std::ostream& os, const Pair& pair) {
    if (pair.tail_) {
        if (pair.tail_->type_ == Type::Pair) {
            // tail is a pair: print multiple elements list-style
            os << pair.head_ << ' ';
            printPair(os, (Pair&)(*pair.tail_));
        } else {
            // non-pair tail: print dotted-pair style
            os << pair.head_ << " . " << pair.tail_;
        }
    } else {
        // no tail: print single element
        os << pair.head_;
    }
}

void Pair::print(std::ostream& os) const {
    os << '(';
    printPair(os, *this);
    os << ')';
}
