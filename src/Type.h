#pragma once

#include <bits/stdint-intn.h>
#include <cstdint>
#include <memory>
#include <string>
#include <iostream>

#include "Util.h"

enum class Type {
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

class Object;
class Pair;

typedef std::shared_ptr<Object> MutableRef;
typedef std::shared_ptr<const Object> Ref;

/// Abstract base class of all objects in Cam Lisp.
class Object : private NoCopy  {
public:
    // TODO: don't need to have separate Type and vtable fields. Do something like Objective-C isa
    const Type type_ = Type::Null;
    // TODO: metadata

    Object() = default;
    Object(const Type& t);

    virtual ~Object() = default;

    /// print an object to an output stream. TODO -- different print strategies e.g printing human-readable output,
    /// printing evalable output, pretty printing
    //
    // TODO -- make these all "Methods" instead of C++ methods.
    virtual void print(std::ostream& os) const = 0;

    // TODO
    // virtual Ref eval() const  = 0;
    // virtual Ref invoke(std::shared_ptr<const Pair> args) const;
    // virtual MutableRef invokeMutable(std::shared_ptr<Pair> args);
};
// TODO -- why do we need separate const and non-const versions?
std::ostream& operator<<(std::ostream& os, Ref object);

class Symbol: public Object {
public:
    // TODO -- use the utf8 string type here instead!
    const std::string value_;

    Symbol(const std::string& value);

    virtual ~Symbol() override = default;

    operator const std::string&() const { return value_; }

    inline static Ref make(const std::string& value) { return std::make_shared<const Symbol>(value); }

    virtual void print(std::ostream& os) const override;
};

class Pair: public Object {
public:
    Ref head_ = nullptr;
    Ref tail_ = nullptr;

    Pair();
    Pair(Ref head, Ref tail);

    virtual ~Pair() override = default;

    inline static Ref make() { return std::make_shared<const Pair>(); }
    inline static Ref make(Ref head, Ref tail) { return std::make_shared<const Pair>(head, tail); }

    virtual void print(std::ostream& os) const override;
};

// TODO -- Integer should always be pass-by-value instead of pass-by-reference!

/// 64-bit integer type.
class Int64 : public Object {
public:
    // TODO -- should this be atomic?
    const std::int64_t value_ = 0;

    Int64();
    Int64(int64_t value);

    virtual ~Int64() override = default;

    inline static Ref make() { return std::make_shared<Int64>(); }
    inline static Ref make(int64_t value) { return std::make_shared<Int64>(value); }

    operator int64_t() const { return value_; }

    virtual void print(std::ostream& os) const override;
};
