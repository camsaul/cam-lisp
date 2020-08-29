#include <memory>
#include <readline/chardefs.h>
#include <string>

#include "tao/pegtl.hpp"

#include "Parse.h"
#include "Type.h"
#include "tao/pegtl/ascii.hpp"
#include "tao/pegtl/rules.hpp"

typedef std::vector<std::vector<Ref>> Objects;
typedef std::vector<std::vector<std::string>> RawForms;

template <typename Item>
void debugPrint(std::string message, const std::vector<std::vector<Item>>& stack) {
    std::cout << message << std::endl;

    int i = 0;
    for (const auto& frame : stack) {
        std::cout << '[' << i++ << "] ";
        for (const auto& item : frame) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}

namespace p = tao::pegtl;
namespace u = tao::pegtl::utf8;

// See https://github.com/taocpp/PEGTL/blob/master/doc/Rule-Reference.md

typedef p::space whitespace;

struct sexpr;

// Valid characters that can go in a symbol. Anything printable except whitespace or ()\"
struct symbolChar:
  p::seq<p::not_at<whitespace>,
         p::not_at<p::one<'(', ')', '\'', '"'>>,
         p::print>
{};

// a symbol is one or more symbol chars but cannot start with a number.
struct symbol:
  p::plus<symbolChar>
  // p::seq<p::seq<p::not_at<p::digit>,
  //               symbolChar>,
  //        p::star<symbolChar>>
{};

struct integer :
    p::seq<p::opt<u::one<'+', '-'>>,
           p::plus<p::digit>>
{};

struct atom :
  p::sor<integer, symbol>
{};

struct listBegin :
    u::one<'('>
{};

struct list :
  p::seq<listBegin,
         p::star<sexpr>,
         u::one<')'>>
{};

struct sexpr :
    p::pad<p::sor<atom, list>, whitespace>
{};


struct grammar :
    p::star<sexpr>
{};

template <typename Rule>
struct action {};

template <>
struct action<integer> {
    template <typename actionInput>
    static void apply(const actionInput& in, Objects& objects, RawForms& rawForms) {
        // std::cout << "in.string() = " << in.string() << std::endl;
        objects.back().push_back(Int64::make(std::stoi(in.string())));
        rawForms.back().push_back(in.string());
    }
};

template<>
struct action<listBegin> {
    template <typename actionInput>
    static void apply(const actionInput& in, Objects& objects, RawForms& rawForms) {
        debugPrint("before list: " + in.string(), objects);

        objects.emplace_back();
        rawForms.emplace_back();
    }
};

Ref makeList(const std::vector<Ref>& items) {
    Ref result = nullptr;
    for (auto itr = items.crbegin(); itr != items.crend(); itr++) {
        result = Pair::make(*itr, result);
    }
    return result;
}

template <>
struct action<list> {
    template <typename actionInput>
    static void apply(const actionInput& in, Objects& objects, RawForms& rawForms) {
        debugPrint("<list>", objects);

        const std::vector<Ref> items  = objects.back();

        objects.pop_back();
        objects.back().push_back(makeList(items));

        rawForms.pop_back();
        rawForms.back().push_back(in.string());

        debugPrint("</list>", objects);
    }
};

template <>
struct action<symbol> {
    template <typename actionInput>
    static void apply(const actionInput& in, Objects& objects, RawForms& rawForms) {
      objects.back().push_back(Symbol::make(in.string()));
      rawForms.back().push_back(in.string());
    }
};

Reader::Result Reader::read(std::string::const_iterator& it, const std::string::const_iterator& end)  {
    Objects objects;
    RawForms rawForms;

    objects.emplace_back();
    rawForms.emplace_back();

    auto parserInput = p::memory_input(&*it, &*end, "");

    p::parse<grammar, action>(parserInput, objects, rawForms);

    // std::cout << "[byte] " << parserInput.byte() << std::endl
    //           << "[line] " << parserInput.line() << std::endl
    //           << "[column] " << parserInput.byte_in_line() << std::endl;

    // std::cout << "objects.size() = " << objects.size() << std::endl;

    // for (const auto& item : objects) {
    //     std::cout << "OUTPUT = " << item << std::endl;
    // }

    it += parserInput.byte();

    auto status =
        (objects.size() && it == end) ?
        Reader::Status::Ok :
        it == end ?
        Reader::Status::Empty :
        Reader::Status::Incomplete;

    return { status, rawForms.front(), objects.front() };
}
