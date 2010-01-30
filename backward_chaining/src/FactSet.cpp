#include "FactSet.h"
#include "eval.h"

FactSet::FactSet(std::vector<Fact *> facts) : _facts(facts)
{
}

FactSet::~FactSet()
{
}

Fact*	FactSet::operator[](int	i)
{
  if (i >= 0 && i < this->_facts.size())
    {
      return (this->_facts[i]);
    }
  return NULL;
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

bool	FactSet::exist(char name)
{
  int	i, max;
  max = this->_facts.size();
  for (i = 0 ; i < max; ++i)
    {
      if (this->_facts[i]->_name == name)
	return true;
    }
  return false;
}

//get first fact
Fact*	FactSet::selectFact()
{
  if (this->_facts.size())
    return (this->_facts[0]);
  return NULL;
}

Fact*	FactSet::getFactByName(Fact* fact)
{
  int	i, max;
  for (i = 0, max = this->_facts.size(); i < max; ++i)
    {

      if (this->_facts[i]->_name == fact->_name)
	{
	  return this->_facts[i];
	}
    }
  return NULL;
}

Fact*	FactSet::getFactByName(char factName)
{
  int	i, max;
  for (i = 0, max = this->_facts.size(); i < max; ++i)
    {

      if (this->_facts[i]->_name == factName)
	{
	  return this->_facts[i];
	}
    }
  return NULL;
}

void	FactSet::display()
{
  int	i, max;
  for (i = 0, max = this->_facts.size(); i < max; ++i)
    {
      this->_facts[i]->display();
    }
}


int	FactSet::size()
{
  return (this->_facts.size());
}

//ne set pas Si existe dans la base et IsConst, sinon set
void	FactSet::setValFromConclusion(std::string const & conclusion)
{
  int	i, max;
  for (i = 0, max = conclusion.size(); i < max; ++i)
    {
      if (isCaps(conclusion[i]))
	{
	  Tribool smartval = smartvalue(i, conclusion);
	  if (this->exist(conclusion[i]))
	    {
	      Fact* fact = this->getFactByName(conclusion[i]);
	      if (fact != NULL && !fact->_isConst)
		fact->_value = smartval;
	    }
	  else
	    {
	      Fact* fact = new Fact(conclusion[i], smartval, 0);
	      this->add(fact);
	    }
	}
    }
}
