#include <memory>
#include <string>

#include "tao/pegtl.hpp"

#include "Parse.h"
#include "Type.h"

namespace grammar {
    using namespace tao::pegtl; // TODO -- use ::utf8 namespace?

    // See https://github.com/taocpp/PEGTL/blob/master/doc/Rule-Reference.md

    struct integer :
        seq<opt<one<'+', '-'>>,
            plus<digit>>
    {};

    struct Grammar :
        until<integer>
    {};
}

namespace action {
    using namespace tao::pegtl;
    using namespace grammar;

    template <typename Rule>
    struct Action :
        nothing<Rule>
    {};

    template <>
    struct Action<integer> {
        template <typename ActionInput>
        static void apply(const ActionInput& in, std::vector<Ref>& out) {
            // std::cout << "in.string() = " << in.string() << std::endl;
            out.push_back(Int64::make(std::stoi(in.string())));
        }
    };
}

Reader::Result Reader::read(std::string::const_iterator& it, const std::string::const_iterator& end)  {
    using namespace tao;

    std::vector<Ref> output;

    auto parserInput = pegtl::memory_input(&*it, &*end, "");

    pegtl::parse<grammar::Grammar, action::Action>(parserInput, output);

    // std::cout << "[byte] " << parserInput.byte() << std::endl
    //           << "[line] " << parserInput.line() << std::endl
    //           << "[column] " << parserInput.byte_in_line() << std::endl;

    // std::cout << "output.size() = " << output.size() << std::endl;

    // for (const auto& item : output) {
    //     std::cout << "OUTPUT = " << item << std::endl;
    // }

    if (output.size() == 1) {
        it += parserInput.byte();
        return Result { Reader::Status::Ok, output[0] };
    } else {
        return Result { Reader::Status::Incomplete, nullptr };
    }
}
