#pragma once

#include <bits/stdint-intn.h>
#include <cstdint>
#include <memory>
#include <string>
#include <iostream>

#include "Util.h"

enum class Type2 {
    Null = 0,
    T,
    // TODO: Boolean?
    // TODO: Type?
    Symbol,
    // TODO: keyword?
    Pair,
    // TODO Number,
    // TODO Byte/Int8, Int16, Int32
    Int64
    // TODO: Int128, Int256, Int512 (?)
    // TODO: Other number types
    // TODO: String
    // TODO: Vector?
    // TODO: Stream
    // TODO: Function
    // TODO: Method(?)
};

/// Abstract base class of all objects in Cam Lisp.
class Object2 : private NoCopy  {
public:
    // Don't need to have separate Type2 and vtable fields. Do something like Objective-C isa
    Type2 type_= Type2::Null;

    Object2() = default;
    Object2(const Type2& t);

    virtual ~Object2() = default;

    /// print an object to an output stream. TODO -- different print strategies e.g printing human-readable output,
    /// printing evalable output, pretty printing
    virtual void print(std::ostream& os) const = 0;
};

typedef std::shared_ptr<Object2> Object2Ptr;
typedef std::shared_ptr<const Object2> ConstObject2Ptr;

inline std::ostream& operator<<(std::ostream& os, const Object2& object) {
    object.print(os);
    return os;
}

// TODO -- why do we need separate const and non-const versions?
std::ostream& operator<<(std::ostream& os, const Object2Ptr object);
std::ostream& operator<<(std::ostream& os, const ConstObject2Ptr object);

class Symbol: public Object2 {
public:
    std::string value_;

    Symbol(const std::string& value);

    virtual ~Symbol() override = default;

    operator const std::string&() const { return value_; }

    inline static Object2Ptr make(const std::string& value) { return std::make_shared<Symbol>(value); }

    virtual void print(std::ostream& os) const override;
};

class Pair: public Object2 {
public:
    Object2Ptr head_ = nullptr;
    Object2Ptr tail_ = nullptr;

    Pair();
    Pair(Object2Ptr head, Object2Ptr tail);

    virtual ~Pair() override = default;

    inline static Object2Ptr make() { return std::make_shared<Pair>(); }
    inline static Object2Ptr make(Object2Ptr head, Object2Ptr tail) { return std::make_shared<Pair>(head, tail); }

    virtual void print(std::ostream& os) const override;
};

// TODO -- Integer should always be pass-by-value instead of pass-by-reference!

/// 64-bit integer type.
class Int64 : public Object2 {
public:
    // TODO -- should this be atomic?
    std::int64_t value_ = 0;

    Int64();
    Int64(int64_t value);

    virtual ~Int64() override = default;

    inline static Object2Ptr make() { return std::make_shared<Int64>(); }
    inline static Object2Ptr make(int64_t value) { return std::make_shared<Int64>(value); }

    operator int64_t() const { return value_; }

    virtual void print(std::ostream& os) const override;
};

/// ****************************************************************************************************
/// core functions ! TODO -- move to a different file.
/// ****************************************************************************************************

inline Object2Ptr cons(Object2Ptr head, Object2Ptr tail) {
    return Pair::make(head, tail);
}

/// ****************************************************************************************************
/// M E T H O D S
/// ****************************************************************************************************
