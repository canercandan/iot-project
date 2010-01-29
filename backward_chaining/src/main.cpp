#include <istream>
#include <fstream>
#include <iostream>
#include <vector>

#include "parsing.hpp"
#include "RuleSet.h"
#include "FactSet.h"
#include "backward_chaining.h"

std::vector<Rule *> construct_rules();
std::vector<Fact *> construct_facts();





void    parse_file(char const * file_name)
{
//     std::filebuf fb;
//     std::istream is(&(fb));

//     fb.open(file_name, std::ios::in);

//     std::string str;
//     while (getline(is, str))
//     {
//         truc ee(15);
//         std::vector<Rule> v;
//         if (client::parse_numbers(str.begin(), str.end(), v))
//         {
//             std::cout << "-------------------------\n";
//             std::cout << "Parsing succeeded\n";
//             std::cout << str << " Parses OK: " << std::endl;

//             //for (std::vector<Rule>::size_type i = 0; i < v.size(); ++i)
//             //    std::cout << i << ": " << v[i] << std::endl;

//             std::cout << "\n-------------------------\n";
//         }
//         else
//         {
//             std::cout << "-------------------------\n";
//             std::cout << "Parsing failed\n";
//             //std::cout << str << std::endl;
//             std::cout << "-------------------------\n";
//         }
//     }

//     fb.close();
}

int	main(int ac, char **av)
{
  if (av[1] == NULL || ac != 2)
    {
      std::cerr << "usage: ./BackwardChaining File.txt"<< std::endl;
      return (1);
    }
  parse_file(av[1]);

  std::vector<Fact *> facts;
  std::vector<Rule *> rules;
  facts = construct_facts();
  rules = construct_rules();
  RuleSet	ruleset(rules);
  FactSet	factset(facts);
  Fact* searchFact = new Fact('C', UNDEF, 0);
  int result = resolve_fact(searchFact, ruleset, factset);
  std::cout<< "Result :" << result << std::endl;
  return 0;
}

std::vector<Rule *> construct_rules()
{
  std::vector<Rule *> rules;
  Rule* r1;

  r1 = new Rule("R1", "A", "C");
  rules.push_back(r1);
  return rules;
};

std::vector<Fact *> construct_facts()
{
  std::vector<Fact *> facts;

  Fact* a;
  //Fact* b;

  a = new Fact('A', TRUE, 1);
  //b = new Fact('B', TRUE, 1);

  facts.push_back(a);
  //facts.push_back(b);
  return facts;
};

