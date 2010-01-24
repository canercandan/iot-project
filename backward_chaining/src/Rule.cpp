#include "Rule.h"
#include <iostream>

Rule::Rule(const std::string name, const std::string proposition, const std::string conclusion)
  : _name(name), _proposition(proposition), _conclusion(conclusion), _burned(false)
{

}


Rule::~Rule()
{
  std::cout<< "~Rule( " << this->_name << " )"<<std::endl;
}

bool Rule::isBurned() const
{
  return (this->_burned);
}

std::string const & Rule::getConclusion() const
{
  return (this->_conclusion);
}

void	Rule::burn()
{
  this->_burned = true;
}

FactSet Rule::getFactFromProposition()
{
  FactSet		facts(std::vector<Fact *>(0));
  unsigned int		i;
  unsigned int		max;

  max = this->_proposition.length();
  for (i = 0; i < max ; ++i)
    {
      char	c = this->_proposition[i];
      if (c >= 'A' &&  c <= 'Z')
	{
	  /*on connait rien sur ce Fact encore, sauf son nom*/
	  Fact* fact = new Fact(c, UNDEF, 0);
	  facts.add(fact);
	}
    }
  return (facts);
}

std::string const & Rule::getName() const
{
  return (this->_name);
}
