#include <istream>
#include <fstream>
#include <iostream>
#include <vector>

#include "parsing.hpp"
#include "Rule.h"
#include "Fact.h"
#include "RuleSet.h"
#include "FactSet.h"


std::vector<Rule *> construct_rules();
std::vector<Fact *> construct_facts();
bool truth_value(Fact* fact, RuleSet & ruleset, FactSet& knownfacts);



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

/*Retourne vrai si la regle est brulable*/
bool	fire_ability(Rule rule, RuleSet & ruleset, FactSet& facts)
{
  std::cout<< "Fire Ability Rule :"<< rule.getName() << std::endl;
  int	i;
   /* retourne ts les facts dans la proposition*/
  FactSet facts_to_check = rule.getFactFromProposition();
  /*
    getFirst ou va taper dans la table de tous les facts
   et ne prend que les facts unkown
   */
  Fact* fact = facts_to_check.selectFact();
  while (fact != NULL)
    {
      if (!truth_value(fact, ruleset, facts))
        {
	  std::cout<< "Fire ability " << rule.getName() << " False" << std::endl;
	  return false;
	}
      facts_to_check.remove(fact);
      fact = facts_to_check.selectFact();
    }
  std::cout<< "Fire ability " << rule.getName() << " True" << std::endl;
  return (true);
}

/*retourne vrai si on peut evaluer le fact,
??et/ ou si le fact correspond exactement mais dans ce cas remplir les facts donnes*/
bool truth_value(Fact *fact, RuleSet & ruleset, FactSet& knownfacts)
{
  std::cout<< "Truth value: " << fact->_name << std::endl;
  /*
    si Fact existe dans les knowns facts 
    //pas sur& que sa valeur correspond exactement => return true
  */
  if (knownfacts.exist(fact))
    {
      std::cout<< "Le fact" << fact->_name <<  " existe dans la base" << std::endl;
      std::cout<< "Truth value "<< fact->_name<< " true " << std::endl;
      return true;
    }
  int	indice = ruleset.concludingRule(*fact);
  while (indice != -1)
    {
      Rule* cur = ruleset._ruleset[indice];
      cur->burn();
      if (fire_ability(*cur, ruleset, knownfacts))
	{
	  //Pbm -> Si la conclusion est impossible ne pas ajouter le fact et ne pas retourner true
	  //Setter le fact selon la conclusion
	  std::cout<< "truth Value: " << fact->_name << "true" << std::endl;
	  knownfacts.add(fact);
	  return true;
	}
    }
  std::cout<< "truth Value: " << fact->_name << "false" << std::endl;
  return false;
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
  truth_value(searchFact, ruleset, factset);
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
  Fact* b;

  a = new Fact('A', TRUE, 1);
  //b = new Fact('B', TRUE, 1);

  facts.push_back(a);
  facts.push_back(b);
  return facts;
};

