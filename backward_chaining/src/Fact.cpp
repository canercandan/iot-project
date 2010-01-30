#include "Fact.h"
#include <iostream>

/*les const sont ceux de la base initiale*/
Fact::Fact(const char name, Tribool  value, bool isConst)
  : _name(name), _value(value), _isConst(isConst)
{
}

Fact::~Fact()
{
}

void	Fact::display()
{
  std::cout<< "Fact " << this->_name << "   ";
  std::cout <<  this->_value;
  //   if (this->_isConst)
  //     {
  //       std::cout<< " isConst " <<std::endl;
  //     }
  //   else
  //     std::cout<< " isNotConst " <<std::endl;
}

//Setter le fact selon la conclusion => A true,  !A false
void	Fact::setValFromConclusion(std::string const & conclusion)
{
  int	i, max;
  for (i = 0, max = conclusion.size(); i < max; ++i)
    {
      if (conclusion[i] ==  this->_name)
	{
	  if (i > 0)
	    {
	      if (conclusion[i - 1] == '!')
		this->_value = Tribool(0);
	      else
		this->_value = Tribool(1);
	    }
	  else
	    this->_value = Tribool(1);
	}
    }
}
