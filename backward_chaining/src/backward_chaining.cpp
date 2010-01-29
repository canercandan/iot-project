#include <stdlib.h>
#include <iostream>
#include "backward_chaining.h"


/* retourne la valeur du fact */
Tribool resolve_fact(Fact *fact, RuleSet & ruleset, FactSet& knownfacts)
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
      return Tribool(knownFact->_value);
    }

  //recupere les regles de ce fact
  int	indice = ruleset.concludingRule(*fact);

  while (indice != -1)
    {
      std::cout << "Indice" << std::endl;
      Rule* cur = ruleset._ruleset[indice];
      //cur->burn();
      Tribool rule = resolve_rule(*cur, ruleset, knownfacts);
      std::cout<< "la regle: " <<  cur->getName() << rule << std::endl;

      if (rule._value == 1)
	{
	  fact->setValFromConclusion(ruleset._ruleset[indice]->getConclusion());
	  knownfacts.add(fact);
	  return Tribool(1);
	}
      indice = ruleset.concludingRule(*fact);
    }
  //std::cout<< "le Fact: " << fact->_name << " false" << std::endl;
  return Tribool(2);
}

/*Retourne vrai si la regle est brulable cad si lexpr booleene est true ou alors si elle a pu etre evalué ??  a voir*/
Tribool	resolve_rule(Rule& rule, RuleSet & ruleset, FactSet& facts)
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
      resolve_fact(facts_to_check[i], ruleset, facts);
    }
  Tribool evalexpr = eval_expr(facts_to_check, rule);
  std::cout<< "eval_expr " << rule.getName() << evalexpr << std::endl;
  rule.burn();
  return evalexpr;
}



Tribool	eval_expr(FactSet & facts, Rule& rule)
{
  std::cout<< rule.getProposition() << std::endl;
  //   int i, max;
  //   bool ret = 1;
  //   for (i= 0, max = facts.size(); i < max; ++i)
  //     {
  //       ret = ret && facts[i]->_value._value;
  //     }
  //   return ret;
  // A & B | C & D;
  //   boule = eval_et(a, b)
  //   boule =  boule || eval_et(c, d);
  //     return boule A.value & B.value)
  std::string proposition = rule.getProposition();
  int i = 0;
  return (eval_all(&i, proposition, facts));
}


Tribool eval_all(int *i, std::string proposition, FactSet& facts)
{
  std::cout<< "eval_all"<< std::endl;
  Tribool ret = eval_unit(i, proposition, facts);
  std::cout<< *i <<std::endl;
  while (proposition[*i] != '\0')
    {
      std::cout<< *i<< " : ["<< proposition[*i]<< "]" << std::endl;
      if (proposition[*i] == '&')
	{
	  ret = ret & eval_unit(i, proposition, facts);
	}
      if (proposition[*i] == '|')
	{
	  // si ret est vrai retourne vrai
	  // si eval_all(&i); est vrai retourne vrai
	  (*i)++;// = *i  + 1;
	  ret = ret | eval_all(i, proposition, facts);
	}
      if (proposition[*i] != '\0')
	(*i)++;
    }
  return ret;
}


Tribool eval_unit(int *i, std::string& proposition,   FactSet & facts)
{
  std::cout<< "eval_unit" << std::endl;
  while (proposition[*i] == ' ')
    (*i)++;
  Tribool op = Tribool(1);
  if (proposition[*i] == '!')
    {
      op._value = false;
      (*i)++;
    }

   while (proposition[*i] == ' ')
     (*i)++;

  if (isCaps(proposition[*i]))
    {
      Tribool factval = facts.getFactByName(proposition[*i])->_value;
      op = (op == factval);
      (*i)++;
    }

  std::cout<< "-----------------------------" << std::endl;
  while (proposition[*i] == ' ')
    {
      (*i)++;
    }
  std::cout<< "++++++++++++++++++++++++++++++++++" << std::endl;
  return op;
}



bool isCaps(char c)
{
  if (c >= 'A' && c <= 'Z')
    return true;
  return false;
}
