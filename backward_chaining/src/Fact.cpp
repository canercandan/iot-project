#include "Fact.h"
#include <iostream>

/*les const sont ceux de la base initiale*/
Fact::Fact(const char name, char value, bool isConst)
  : _name(name), _value(value), _isConst(isConst) 
{
}

Fact::~Fact()
{
}

void	Fact::display()
{
  std::cout<< "Fact " << this->_name << "   "<<  this->_value << std::endl;
}
