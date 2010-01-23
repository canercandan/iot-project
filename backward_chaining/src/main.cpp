#include <istream>
#include <fstream>
#include <iostream>
#include <vector>

#include "parsing.hpp"
#include "Rule.h"
#include "Fact.h"
#include "RuleSet.h"

std::vector<Rule *> construct_rules();
std::vector<Fact *> construct_facts();


std::vector<Fact *>& condition(Rule& rule)
{
}


int	getPosition(Fact fact , std::vector<Fact *>& facts)
{
  int	i, max;
  max  = facts.size();
  for (i = 0; i < max; ++i)
    {
      if (fact._name == facts[i]._name)
	return (i);
    }
    return (-1);
}

Fact select_fact(std::vector<Fact *>& facts)
{
}

bool fire_ability(Rule rule, RuleSet & ruleset, std::vector<Fact *>& facts)
{
  int	i;
//   facts_set facts_to_check  condition(R)
//     WHILE facts_to_check ≠ ∅ DO
//     fact F  select_fact(facts_to_check)
//     IF truth_value(F,rules,facts) = false
//           THEN RETURN false
//   facts_to_check  facts_to_check - F
// ENDWHILE
  std::vector<Fact *>& facts_to_check = rule.getCondition();
  Fact fact = select_fact(facts_to_check);
  while (facts_to_check.size())
    {
      if (!truth_value(fact, rules, facts))
        return false;
      i = getPosition(fact, facts_to_check);
      facts_to_check.erase(indice);
    }
  return (true);
}

bool truth_value(Fact fact, RuleSet & ruleset, std::vector<Fact *>& facts)
{
  std::cout<< "Truth value: " << fact._name <<std::endl;
  int	indice = ruleset.concludingRule(fact);
  while (indice != -1)
    {
      Rule* cur = ruleset._ruleset[indice];
      cur->burn();
      if (fire_ability(*cur, ruleset, facts))
	{
	  std::cout<< "truth Value: " << fact._name << "true" << std::endl;
	  return true;
	}
    }
  std::cout<< "truth Value: " << fact._name << "false" << std::endl;
  return false;
}


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
      std::cerr << "usage: ./BackwardChaining RulesFile.txt"<< std::endl;
      return (1);
    }

  parse_file(av[1]);

  std::vector<Fact *> facts;
  std::vector<Rule *> rules;
  facts = construct_facts();
  rules = construct_rules();
  RuleSet ruleset(rules);
  Fact searchFact("C", UNDEF);
  truth_value(searchFact, ruleset, facts);
  return 0;
}


std::vector<Rule *> construct_rules()
{
  std::vector<Rule *> rules;


  Rule* r1;
  Rule* r2;
  Rule* r3;

  r1 = new Rule("R1", "A & B", "C");
  r2 = new Rule("R2", "B & C", "D");
  r3 = new Rule("R3", "C & D", "E");

  rules.push_back(r1);
  rules.push_back(r2);
  rules.push_back(r3);
  return rules;
};



std::vector<Fact *> construct_facts()
{
  std::vector<Fact *> facts;


  Fact* a;
  Fact* b;
  Fact* c;
  Fact* d;
  Fact* e;
  Fact* f;

  a = new Fact("A", TRUE);
  b = new Fact("B", TRUE);
  c = new Fact("C", TRUE);
  d = new Fact("D", TRUE);
  e = new Fact("E", TRUE);
  f = new Fact("F", TRUE);

  facts.push_back(a);
  facts.push_back(b);
  facts.push_back(c);
  facts.push_back(d);
  facts.push_back(e);
  facts.push_back(f);
  return facts;
};

