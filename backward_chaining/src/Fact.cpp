#include "Fact.h"
#include <iostream>

/*les const sont ceux de la base initiale*/
Fact::Fact(const char name, int value, bool isConst)
  : _name(name), _value(value), _isConst(isConst) 
{
}

Fact::~Fact()
{
}

void	Fact::display()
{
  std::cout<< "Fact " << this->_name << "   "<<  this->_value;
  if (this->_isConst)
    {
      std::cout<< " isConst " <<std::endl;
    } 
  else
      std::cout<< " isNotConst " <<std::endl;
}
