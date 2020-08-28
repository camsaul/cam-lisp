#include <boost/spirit/home/qi/numeric/real.hpp>
#include <boost/variant/detail/apply_visitor_unary.hpp>
#include <boost/variant/static_visitor.hpp>
#include <string>

#define BOOST_SPIRIT_USE_PHOENIX_V3
// #include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/include/qi.hpp>
// #include <boost/phoenix/phoenix.hpp>
#include <boost/variant.hpp>

#include "Parse.h"
#include "Type.h"

// using namespace boost;
using namespace boost::spirit;

// template <typename Iterator, typename Skipper>
// struct Grammar : qi::grammar<Iterator, Results(), Skipper> {
//     Grammar() : Grammar::base_type{values} {
//         value = qi::int_ | qi::bool_;
//         values = value % ',';
//     }
//     qi::rule<Iterator, Result(), Skipper> value;
//     qi::rule<Iterator, Results(), Skipper> values;
// };

// using qi::lexeme;
// using qi::char_;
// using namespace qi::labels;
// // using qi::string;

// token %= +(char_ -'(' -')' -'#' -'"' -qi::space);

// list %= '(' >> *node >> ')';

// node %= (token|list);

// struct Grammar2 : qi::grammar<std::string::iterator, Ref, ascii::space_type> {
//     bool match = false;
//     Ref
//     qi::rule<std::string::iterator, Ref(), ascii::space_type> rule;

//     Grammar2(): Grammar2::base_type(sexpr) {
//         value = qi::int_[(
//                 [](int i) {
//                     this->match_ = true;
//                     this->sexpr_ = Int64::make(i);
//                 })];
//     }
// };ma

class Visitor : public boost::static_visitor<Ref> {
public:
    Ref operator()(int i) const {
        return Int64::make(i);
    }
};

Reader::Result Reader::read(std::string::const_iterator& it, const std::string::const_iterator& end) {
    // auto grammar =
    //     qi::int_[([result](int i) mutable {
    //                   result = Int64::make(i);
    //               })];

    // auto grammar =
    //     qi::int_[phoenix::ref(result) = Int64::make(static_cast<int>(qi::_1))];

    // See https://www.boost.org/doc/libs/1_74_0/libs/spirit/doc/html/spirit/qi/quick_reference/qi_parsers/operator.html

    auto grammar =
        qi::int_ |
        qi::float_;

    boost::variant<int, float> parsed;

    bool match = qi::phrase_parse(it, end, grammar, ascii::space, parsed);

    auto result = boost::apply_visitor(Visitor(), parsed);

    return (match
            ? Result { Reader::Status::Ok, result }
            : (it == end
               ? Result { Reader::Status::Empty, nullptr }
               : Result { Reader::Status::Incomplete, nullptr }));

}
