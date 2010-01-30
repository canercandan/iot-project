#include <istream>
#include <fstream>
#include <iostream>
#include <vector>

#include "parsing.hpp"
#include "RuleSet.h"
#include "FactSet.h"
#include "Tribool.h"
#include "backward_chaining.h"

std::vector<Rule *> construct_rules();
std::vector<Fact *> construct_facts();

void    parse_file(char const * file_name, std::vector<Rule *>& v, std::vector<Fact *>& f)
{
    std::filebuf fb;
    std::istream is(&(fb));

    fb.open(file_name, std::ios::in);

    std::string str;
    while (getline(is, str))
    {
        std::cout << "-------------------------\n";
        if (client::parse_numbers(str.begin(), str.end(), v, f))
        {
            std::cout << "Parsing success\n";
        }
        else
        {
            std::cout << "Parsing failed\n";
        }
        std::cout << "-------------------------\n";
    }

    fb.close();
}

int main(int ac, char **av)
{
    if (av[1] == NULL || ac != 2)
    {
        std::cerr << "usage: ./BackwardChaining File.txt"<< std::endl;
        return (1);
    }
    std::vector<Fact *> facts;
    std::vector<Rule *> rules;

    parse_file(av[1], rules, facts);

    RuleSet   ruleset(rules);
    FactSet   factset(facts);

    Fact* searchfact1 = new Fact('E', Tribool(2), 0);
    Fact* searchfact2 = new Fact('F', Tribool(2), 0);
    std::vector<Fact *> searchfacts;
    searchfacts.push_back(searchfact1);
    searchfacts.push_back(searchfact2);

    int i, max;
    for (i = 0, max = searchfacts.size(); i < max; ++i)
      {
	Tribool result = resolve_fact(searchfacts[i], ruleset, factset);
	std::cout<< "Final Result :" << result << std::endl;
      }
    return 0;
}
