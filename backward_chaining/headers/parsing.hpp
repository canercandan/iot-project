#ifndef __PARSING_HPP__
#define __PARSING_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <string>
#include <vector>

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    template <typename Iterator>
        bool parse_numbers(Iterator first, Iterator last, std::vector<std::string>& rules)
        {
            using qi::print;
            using qi::phrase_parse;
            using qi::_1;
            using qi::lit;
            using ascii::space;
            using phoenix::push_back;
            using phoenix::ref;

            bool r = phrase_parse(first, last,

                    (
                     lit('R') >> lit(':') >> 
                     (+(print))[push_back(ref(rules), _1)]
                     //+(print)
                     )
                    ,
                    space);

            if (first != last) // fail if we did not get a full match
                return false;
            return r;
        }
}

#endif // !__PARSING_HPP__
