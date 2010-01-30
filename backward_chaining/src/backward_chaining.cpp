#include <stdlib.h>
#include <iostream>
#include "backward_chaining.h"
#include "eval.h"

/* retourne la valeur du fact */
Tribool resolve_fact(Fact *fact, RuleSet & ruleset, FactSet& knownfacts)
{
  std::cout<< "Fact " << fact->_name << std::endl;

  if (knownfacts.exist(fact))
    {
      //std::cout<< "Le fact" << fact->_name <<  " existe dans la base" << std::endl;
      //std::cout<< "Resolve Fact "<< fact->_name << " " << fact->_value << std::endl;
      Fact* knownFact = knownfacts.getFactByName(fact);
      //copie du fact
      fact->_value = knownFact->_value;
      fact->_isConst = knownFact->_isConst;
      std::cout<< "Fact " << fact->_name << "   " <<knownFact->_value << std::endl;
      return Tribool(knownFact->_value);
    }

  //recupere les regles de ce fact
  int	indice = ruleset.concludingRule(*fact);
  while (indice != -1)
    {
      Rule* cur = ruleset._ruleset[indice];
      Tribool rule = resolve_rule(*cur, ruleset, knownfacts, fact->_name);
      std::cout<< "Rule " <<  cur->getName() << "  " << rule << std::endl;

      if (rule._value == 1)
	{
	  knownfacts.setValFromConclusion(ruleset._ruleset[indice]->getConclusion());
	  Fact* knownFact = knownfacts.getFactByName(fact);
	  //copie du fact
	  fact->_value = knownFact->_value;
	  fact->_isConst = knownFact->_isConst;
	  std::cout<< "Fact " << fact->_name << "   " << knownFact->_value << std::endl;
	  //fact->setValFromConclusion(ruleset._ruleset[indice]->getConclusion());
	  //knownfacts.add(fact);
	  return Tribool(1);
	}
      indice = ruleset.concludingRule(*fact);
    }
  return Tribool(2);
}

Tribool	resolve_rule(Rule& rule, RuleSet & ruleset, FactSet& facts, char searchFactName)
{
  std::cout<< "Rule "<< rule.getName() << std::endl;
  int	i, max;
  /* retourne ts les facts dans la proposition*/
  FactSet facts_to_check = rule.getFactFromProposition();
  // recup tous les facts
  //std::cout<< "Nombre des facts dans la proposition "<< facts_to_check.size()<< std::endl;
  //  facts_to_check.display();
  for (i = 0, max = facts_to_check.size(); i < max; ++i)
    {
      if (facts_to_check[i]->_name  == searchFactName)
	{
	  rule.burn();
	  return (Tribool(false));
	}
      resolve_fact(facts_to_check[i], ruleset, facts);
    }
  rule.burn();
  Tribool evalexpr = eval_expr(facts_to_check, rule);
  //std::cout<< "eval_expr " << rule.getName() << evalexpr << std::endl;
  return evalexpr;
}
