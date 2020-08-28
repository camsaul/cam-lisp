#include <memory>
#include <string>

#include "tao/pegtl.hpp"

#include "Parse.h"
#include "Type.h"
#include "tao/pegtl/rules.hpp"

typedef std::vector<Ref> Objects;
typedef std::vector<std::string> RawForms;

namespace grammar {
    using namespace tao::pegtl; // TODO -- use ::utf8 namespace?

    // See https://github.com/taocpp/PEGTL/blob/master/doc/Rule-Reference.md

    struct whitespace :
        space
    {};

    struct symbol:
        plus<print>
    {};

    struct integer :
        seq<opt<one<'+', '-'>>,
            plus<digit>>
    {};

    struct atom :
        integer
    {};

    struct sexpr :
        atom
    {};


    struct Grammar :
        star<pad<integer, whitespace>>
    {};
}

namespace action {
    using namespace tao::pegtl;
    using namespace grammar;

    template <typename Rule>
    struct Action {};

    template <>
    struct Action<integer> {
        template <typename ActionInput>
        static void apply(const ActionInput& in, Objects& objects, RawForms& rawForms) {
            // std::cout << "in.string() = " << in.string() << std::endl;
            objects.push_back(Int64::make(std::stoi(in.string())));
            rawForms.push_back(in.string());
        }
    };
}

Reader::Result Reader::read(std::string::const_iterator& it, const std::string::const_iterator& end)  {
    using namespace tao;

    Objects objects;
    RawForms rawForms;

    auto parserInput = pegtl::memory_input(&*it, &*end, "");

    pegtl::parse<grammar::Grammar, action::Action>(parserInput, objects, rawForms);

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

    return { status, rawForms, objects };
}
