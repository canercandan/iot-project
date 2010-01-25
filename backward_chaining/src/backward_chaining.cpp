#include <iostream>
#include "backward_chaining.h"

/* retourne la valeur du fact */
int resolve_fact(Fact *fact, RuleSet & ruleset, FactSet& knownfacts)
{
  std::cout<< "Resolve Fact: " << fact->_name << std::endl;

  
  if (knownfacts.exist(fact))
    {
      std::cout<< "Le fact" << fact->_name <<  " existe dans la base" << std::endl;
      std::cout<< "Resolve Fact "<< fact->_name << " " << fact->_value << std::endl;
      fact = knownfacts.getFactByName(fact);
      return fact->_value;  
    }
  std::cout<< "Le fact" << fact->_name <<  "n existe dans la base" << std::endl;
  //essai de resoudre les regles de ce fact
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
	  return TRUE;
	}
    }
  std::cout<< "truth Value: " << fact->_name << "false" << std::endl;
  return FALSE;
}



/*Retourne vrai si la regle est brulable cad si lexpr booleene est true ou alors si elle a pu etre evalué ??  a voir*/
bool	fire_ability(Rule rule, RuleSet & ruleset, FactSet& facts)
{
  std::cout<< "Fire Ability Rule :"<< rule.getName() << std::endl;
  int	i;
   /* retourne ts les facts dans la proposition*/
  FactSet facts_to_check = rule.getFactFromProposition();
  
  

  //Fact* fact = facts_to_check.getNextFact();
  // recup tous les facts
  

  // eval les unknown facts

  //eval coondition
  

  //return (eval_condition)

  // while (fact != NULL)
  //     {
  //       if (!resolve_fact(fact, ruleset, facts))
  //         {
  // 	  std::cout<< "Fire ability " << rule.getName() << " False" << std::endl;
  // 	  return false;
  // 	}
  //       facts_to_check.remove(fact);
  //       fact = facts_to_check.selectFact();
  //     }
  std::cout<< "Fire ability " << rule.getName() << " True" << std::endl;
  return (true);
}
