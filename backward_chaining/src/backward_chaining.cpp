#include <stdlib.h>
#include <iostream>
#include "backward_chaining.h"

/* retourne la valeur du fact */
int resolve_fact(Fact *fact, RuleSet & ruleset, FactSet& knownfacts)
{
  std::cout<< "Resolve Fact: " << fact->_name << std::endl;
  
  if (knownfacts.exist(fact))
    {
      std::cout<< "Le fact" << fact->_name <<  " existe dans la base" << std::endl;
      //std::cout<< "Resolve Fact "<< fact->_name << " " << fact->_value << std::endl;
      Fact* knownFact = knownfacts.getFactByName(fact);
      //copie du fact
      fact->_value = knownFact->_value;
      fact->_isConst = knownFact->_isConst;
      std::cout<< "huhuhuhuh:" << knownFact->_value << std::endl;
      return knownFact->_value;
    }
  
  //recupere les regles de ce fact
  int	indice = ruleset.concludingRule(*fact);
  
  while (indice != -1)
    {
      Rule* cur = ruleset._ruleset[indice];
      cur->burn();
      bool rule = resolve_rule(*cur, ruleset, knownfacts);
      std::cout<< "la regle: "<<  cur->getName() << rule<< std::endl;
      if (rule)
	{
	  //Pbm -> Si la conclusion est impossible ne pas ajouter le fact et ne pas retourner true
	  //Setter le fact selon la conclusion
	  knownfacts.add(fact);
	  return true;
	}
    }
  //std::cout<< "le Fact: " << fact->_name << " false" << std::endl;
  return FALSE;
}



/*Retourne vrai si la regle est brulable cad si lexpr booleene est true ou alors si elle a pu etre evalué ??  a voir*/
bool	resolve_rule(Rule rule, RuleSet & ruleset, FactSet& facts)
{
  std::cout<< "Resolve rule :"<< rule.getName() << std::endl;
  int	i, max;
   /* retourne ts les facts dans la proposition*/
  FactSet facts_to_check = rule.getFactFromProposition();
  // recup tous les facts
  std::cout<< "Nombre des facts dans la proposition "<< facts_to_check.size()<< std::endl;
  //  facts_to_check.display();

  for (i = 0, max = facts_to_check.size(); i < max; ++i)
    {
      /*eval ts les facts*/
      facts_to_check[i]->display();
      resolve_fact(facts_to_check[i], ruleset, facts); 
      facts_to_check[i]->display();      
    }
  int evalexpr = eval_expr(facts_to_check);
  

  //eval coondition
  std::cout<< "eval_expr " << rule.getName() << evalexpr << std::endl;
  if (evalexpr == 1)
    return (true);
  if (!evalexpr)
    return false;
}



int	eval_expr(FactSet & facts)
{
  int i, max; 
  bool ret = 1;
  for (i= 0, max = facts.size(); i < max; ++i)
    {
      ret = ret && facts[i]->_value;
    }
  return ret;
}
