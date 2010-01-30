#ifndef __PARSING_HPP__
#define __PARSING_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <string>
#include <vector>

#include "Rule.h"
#include "Fact.h"

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    template <typename Iterator>
        bool parse_numbers(Iterator first, Iterator last, std::vector<Rule *>& rules, std::vector<Fact *>& factes, std::vector<Fact *>& sefactes)
        {
            using qi::print;
            using qi::lexeme;
            using qi::phrase_parse;
            using qi::char_;
            using qi::_1;
            using qi::_2;
            using qi::lit;
            using ascii::space;
            using phoenix::push_back;
            using phoenix::ref;

            qi::rule<Iterator, std::string(), ascii::space_type> pars_rule;
            qi::rule<Iterator, std::string(), ascii::space_type> name_rule;
            qi::rule<Iterator, std::string(), ascii::space_type> condition;
            qi::rule<Iterator, std::string(), ascii::space_type> result;

            qi::rule<Iterator, std::string(), ascii::space_type> pars_fact;
            qi::rule<Iterator, std::string(), ascii::space_type> value;

            qi::rule<Iterator, std::string(), ascii::space_type> pars_search;

            std::string str_name_rule = "";
            std::string str_condition = "";
            std::string str_result = "";

            std::vector<char> tab_variable;
            std::string str_value = "";

            std::vector<char> tab_search;

            // Pars Rule
            name_rule %= char_('R') >> +(char_ - ':');
            result %= +(char_);
            condition %= +(char_ - '=');
            pars_rule %= (name_rule[ref(str_name_rule) += _1]
                        >> lit(':')
                        >> condition[ref(str_condition) += _1]
                        >> lit('=')
                        >> result[ref(str_result) += _1]);

            // Pars Fact
            value %= +(char_ - '=');
            pars_fact %= lit('F') >> lit(':')
                         >> +((char_ - '=')[push_back(ref(tab_variable), _1)])
                         >> lit('=')
                         >> value[ref(str_value) += _1];

            // Pars Search
            pars_search %= lit('S') >> lit(':') 
                         >> +(char_[push_back(ref(tab_search), _1)]);

            bool r = phrase_parse(first, last,

                    (
                     pars_rule
                     | pars_fact
                     | pars_search
                    )
                    ,
                    space);

            if (str_name_rule != "" && str_condition != "" && str_result != "")
            {
                size_t size_name_rule = str_name_rule.size();
                str_condition.erase(0, str_name_rule.size());
                str_result.erase(0, str_name_rule.size() + str_condition.size());
                std::cout << "rule : " << str_name_rule << " : " << str_condition << " = " << str_result << std::endl;
                rules.push_back(new Rule(str_name_rule, str_condition, str_result));
            }
            if (tab_variable.size() > 0 && str_value != "")
            {
                str_value.erase(0, tab_variable.size());
                bool bool_value;
                if (str_value == "true")
                    bool_value = 1;
                else
                    bool_value = 0;

                std::vector<char>::iterator it;
                for ( it = tab_variable.begin() ; it < tab_variable.end(); ++it )
                {
		  //std::cout << "variable : " << *it << " = " << bool_value << std::endl;
		  factes.push_back(new Fact(*it, Tribool(bool_value), 1));
                }
            }
            if (tab_search.size() > 0)
            {
                std::vector<char>::iterator it;
                for ( it = tab_search.begin() ; it < tab_search.end(); ++it )
                {
		  //std::cout << "search : " << *it << std::endl;
                    sefactes.push_back(new Fact(*it, Tribool(2), 0));
                }
            }

            if (first != last) // fail if we did not get a full match
                return false;
            return r;
        }
}

#endif // !__PARSING_HPP__
