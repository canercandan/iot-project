#include "FactSet.h"

FactSet::FactSet(std::vector<Fact *> facts) : _facts(facts)
{
}

FactSet::~FactSet()
{
}

void	FactSet::add(Fact* fact)
{
  this->_facts.push_back(fact);
}

void	FactSet::remove(Fact* fact)
{
  std::vector<Fact *>::iterator it = this->_facts.begin();
  std::vector<Fact *>::iterator itend = this->_facts.end();
  for (; it != itend; ++it)
    {
      if ((*it)->_name == fact->_name)
	{
	  this->_facts.erase(it);
	  return ;
	}
    }
}

bool	FactSet::exist(Fact* fact)
{
  int	i, max;
  max = this->_facts.size();
  for (i = 0 ; i < max; ++i)
    {
      if (this->_facts[i]->_name == fact->_name)
	return true;
    }
  return false;
}

Fact*	FactSet::selectFact()
{
  if (this->_facts.size())
    return (this->_facts[0]);
  return NULL;
}
