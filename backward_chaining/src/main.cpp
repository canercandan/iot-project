#include <istream>
#include <fstream>
#include <iostream>

#include "parsing.hpp"
#include "Rule.h"
#include "Fact.h"

void    parse_file(char const * file_name)
{
    std::filebuf fb;
    std::istream is(&(fb));

    fb.open(file_name, std::ios::in);

    std::string str;
    while (getline(is, str))
    {
        truc ee(15);
        std::vector<Rule> v;
        if (client::parse_numbers(str.begin(), str.end(), v))
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << str << " Parses OK: " << std::endl;

            //for (std::vector<Rule>::size_type i = 0; i < v.size(); ++i)
            //    std::cout << i << ": " << v[i] << std::endl;

            std::cout << "\n-------------------------\n";
        }
        else
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            //std::cout << str << std::endl;
            std::cout << "-------------------------\n";
        }
    }

    fb.close();
}

    int	main(int ac, char **av)
    {

        if (av[1] == NULL || ac != 2)
        {
            std::cerr << "usage: ./BackwardChaining RulesFile.txt"<< std::endl;
            return (1);
        }

        parse_file(av[1]);

        Rule	rule1(std::string("Z"), std::string("A & B"));
        Fact	fact1(std::string("A"), TRUE);
        std::cout<< "ca rullezzz"<< std::endl;
        return 0;
    }
