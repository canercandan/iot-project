#include <istream>
#include <fstream>
#include <iostream>
#include <vector>

//#include "parsing.hpp"
#include "RuleSet.h"
#include "FactSet.h"
#include "Tribool.h"
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
  Fact* searchFact = new Fact('F', Tribool(2), 0);
  Tribool result = resolve_fact(searchFact, ruleset, factset);
  searchFact->display();
  //std::cout<< "Result :" << result << std::endl;
  return 0;
}

std::vector<Rule *> construct_rules()
{
  std::vector<Rule *> rules;
  //   Test1
  //   Rule* r1 = new Rule("R1", "B", "A");
  //   Rule* r2 = new Rule("R2", "C", "A");
  //   Rule* r3 = new Rule("R3", "D & E", "B");
  //   Rule* r4 = new Rule("R4", "G & H", "F");
  //   Rule* r5 = new Rule("R5", "I & J", "G");
  //   Rule* r6 = new Rule("R6", "G", "H");
  //   Rule* r7 = new Rule("R7", "L & M", "K");
  //   Rule* r8 = new Rule("R8", "O & P", "L & N");
  //   Rule* r9 = new Rule("R9", "N", "M");

  //   rules.push_back(r1);
  //   rules.push_back(r2);
  //   rules.push_back(r3);
  //   rules.push_back(r4);
  //   rules.push_back(r5);
  //   rules.push_back(r6);
  //   rules.push_back(r7);
  //   rules.push_back(r8);
  //   rules.push_back(r9);

  //test2
  // Rule* r1 = new Rule("R1", "B & C", "A");
  //   Rule* r2 = new Rule("R2", "D & E", "B");
  //   Rule* r3 = new Rule("R3", "B", "C");
  //   rules.push_back(r1);
  //   rules.push_back(r2);
  //   rules.push_back(r3);
  //TEST3
  // Rule* r1 = new Rule("R1", "B & C", "A");
  //   Rule* r2 = new Rule("R2", "D & !E", "B");
  //   Rule* r3 = new Rule("R3", "B", "C");

  //   rules.push_back(r1);
  //   rules.push_back(r2);
  //   rules.push_back(r3);
  
  //TEST4
  Rule* r1 = new Rule("R1", "B | C ", "A");
  Rule* r2 = new Rule("R2", "D & !E", "B");
  Rule* r3 = new Rule("R3", "B", "C");
  Rule* r4 = new Rule("R4", "!G & H", "F");
  Rule* r5 = new Rule("R5", "!E", "!G");
  Rule* r6 = new Rule("R6", "D", "H");
  rules.push_back(r1);
  rules.push_back(r2);
  rules.push_back(r3);
  rules.push_back(r4);
  rules.push_back(r5);
  rules.push_back(r6);
  return rules;
};

std::vector<Fact *> construct_facts()
{
  std::vector<Fact *> facts;

  //test1
  //   Fact* d = new Fact('D', Tribool(1), 1);
  //   Fact* e = new Fact('E', Tribool(1), 1);
  //   Fact*	i = new Fact('I', Tribool(1), 1);
  //   Fact*	j = new Fact('J', Tribool(1), 1);
  //   Fact* o = new Fact('O', Tribool(1), 1);
  //   Fact* p = new Fact('P', Tribool(1), 1);

  //   facts.push_back(d);
  //   facts.push_back(e);
  //   facts.push_back(i);
  //   facts.push_back(j);
  //   facts.push_back(o);
  //   facts.push_back(p);

  //test2
  //   Fact* d = new Fact('D', Tribool(1), 1);
  //   Fact* e = new Fact('E', Tribool(1), 1);


  //   facts.push_back(d);
  //   facts.push_back(e);

  //test3
  //   i) DE = true
  // 		   ii) D = true E = false
  // Fact* d = new Fact('D', Tribool(1), 1);
  //   Fact* e = new Fact('E', Tribool(0), 1);

  //   facts.push_back(d);
  //   facts.push_back(e);

  //test4
//   i) D = false E = true
// 		   ii) DE = true
// 			iii) D = true E = false
  Fact* d = new Fact('D', Tribool(1), 1);
  Fact* e = new Fact('E', Tribool(0), 1);

  facts.push_back(d);
  facts.push_back(e);

  return facts;
};

