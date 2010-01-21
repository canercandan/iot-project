#include "Rule.h"
#include <iostream>

Rule::Rule(const std::string name, std::string expr)
  : _name(name), _expr(expr)
{
  
}


Rule::~Rule()
{
  std::cout<< "~Rule( " << this->_name << " )"<<std::endl;
}
