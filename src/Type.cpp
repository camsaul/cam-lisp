#include "Type.h"
#include <bits/stdint-intn.h>

Object2::Object2(const Type2& t):
    type_(t)
{}

std::ostream& operator<<(std::ostream& os, const Object2Ptr object) {
    if (object) {
        object->print(os);
    } else {
        os << "nil";
    };

    return os;
}

std::ostream& operator<<(std::ostream& os, const ConstObject2Ptr object) {
    if (object) {
        os << object;
    } else {
        os << "nil";
    };

    return os;
}

Symbol::Symbol(const std::string& value):
    Object2 { Type2::Symbol },
    value_(value)
{}

void Symbol::print(std::ostream& os) const {
    os << this->value_;
}

Pair::Pair():
    Object2 { Type2::Pair },
    head_(nullptr),
    tail_(nullptr)
{}

Pair::Pair(Object2Ptr head, Object2Ptr tail):
    Object2 { Type2::Pair },
    head_(head),
    tail_(tail)
{}

Int64::Int64():
    Object2 { Type2::Int64 },
    value_(0)
{}

Int64::Int64(int64_t value):
    Object2 { Type2::Int64 },
    value_(value)
{}

void Int64::print(std::ostream& os) const {
    os << this->value_;
}

void printPair(std::ostream& os, const Pair& pair) {
    if (pair.tail_) {
        if (pair.tail_->type_ == Type2::Pair) {
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
