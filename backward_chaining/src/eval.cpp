#include "eval.h"


Tribool	eval_expr(FactSet & facts, Rule& rule)
{
  //std::cout<< rule.getProposition() << std::endl;
  std::string proposition = rule.getProposition();
  int i = 0;
  return (eval_all(&i, proposition, facts));
}


Tribool eval_all(int *i, std::string proposition, FactSet& facts)
{
  //std::cout<< "eval_all"<< std::endl;
  Tribool ret = eval_unit(i, proposition, facts);
  //std::cout<< *i <<std::endl;
  while (proposition[*i] != '\0')
    {
      if (proposition[*i] == '&')
	{
	  (*i)++;
	  ret = ret & eval_unit(i, proposition, facts);
	}
      if (proposition[*i] == '|')
	{
	  (*i)++;
	  ret = ret | eval_all(i, proposition, facts);
	}
      if (proposition[*i] != '\0')
	(*i)++;
    }
  return ret;
}


Tribool eval_unit(int *i, std::string& proposition,  FactSet & facts)
{
  //std::cout<< "eval_unit" << std::endl;
  //facts.display();
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
      //   std::cout << "the fact "<< proposition[*i] <<std::endl;
      //       std::cout<< "||||||||||-Factval-|||||||||||" << std::endl;
      //       std::cout << factval<< std::endl;
      //       std::cout<< "||||||||||||||||||||||||||||"<< std::endl;
      op = (op == factval);
      (*i)++;
    }
  while (proposition[*i] == ' ')
    (*i)++;
  // std::cout<< "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" <<std::endl;
  //    std::cout<< op <<std::endl;
  //    std::cout<< "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" <<std::endl;
  return op;
}

bool isCaps(char c)
{
  if (c >= 'A' && c <= 'Z')
    return true;
  return false;
}

Tribool smartvalue(int i, std::string const & conclusion)
{
  if (i > 0)
    {
      if (conclusion[i - 1] == '!')
	return Tribool(0);
      else
	return Tribool(1);
    }
  else
    return Tribool(1);
}
