#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>

#include "Parse.h"
#include "String.h"
#include "Util.h"

using namespace boost::spirit;

typedef boost::variant<int, bool> Result;
typedef std::vector<Result> Results;

template <typename Iterator, typename Skipper>
struct Grammar : qi::grammar<Iterator, Results(), Skipper> {
    Grammar() : Grammar::base_type{values} {
        value = qi::int_ | qi::bool_;
        values = value % ',';
    }
    qi::rule<Iterator, Result(), Skipper> value;
    qi::rule<Iterator, Results(), Skipper> values;
};

// using qi::lexeme;
// using qi::char_;
// using namespace qi::labels;
// // using qi::string;

// token %= +(char_ -'(' -')' -'#' -'"' -qi::space);

// list %= '(' >> *node >> ')';

// node %= (token|list);

ObjectPtr Parse(const std::string& s2) {
    std::string s = s2;
    auto it = s.begin();
    Grammar<std::string::iterator, ascii::space_type> g;
    Results v;

    qi::phrase_parse(it, s.end(), g, ascii::space, v);

    {
        std::cout << "Parsed: " << std::boolalpha;
        auto _ = Color(Color::Green);
        for (const auto& result : v) {
            std::cout << result << std::endl;
        }
    }

    return MakeString("\n<ok>");
}
