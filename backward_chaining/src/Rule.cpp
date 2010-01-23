#include "Rule.h"
#include <iostream>

Rule::Rule(const std::string name, const std::string condition, const std::string implication)
  : _name(name), _condition(condition), _implication(implication), _burned(false)
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


std::string const & Rule::getImplication() const
{
  return (this->_implication);
}

void	Rule::burn()
{
  this->_burned = true;
}
