#include "Type.h"

std::ostream& operator<<(std::ostream& os, const Type& rhs) {
    os << rhs.name;
    return os;
}

bool Type::operator==(const Type& rhs) const {
    return this->name == rhs.name;
}
