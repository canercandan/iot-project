#include "Tribool.h"

# define TRUE 1
# define FALSE 0
# define UNDEF 2

Tribool::Tribool(int value) : _value(value)
{
}


Tribool::~Tribool()
{
}


std::ostream& operator<<(std::ostream& os, Tribool& tribool)
{
  std::string display;
  if (tribool._value == 1)
    display = "TRUE";
  if (tribool._value == 0)
    display = "FALSE";
  if (tribool._value == 2)
    display = "UNKNOWN";
  std::cout<< display;
  return (os);
}


Tribool Tribool::operator ==(Tribool  tribool)
{
  if (this->_value == 2 || tribool._value == 2)
    return (Tribool(2));
  return Tribool(this->_value == tribool._value);
}

Tribool Tribool::operator &(Tribool  tribool)
{
  if (this->_value == 0 || tribool._value == 0)
    return (Tribool(0));
  if (this->_value == 2 || tribool._value == 2)
    return (Tribool(2));
  return (Tribool(1));
}

Tribool Tribool::operator |(Tribool  tribool)
{
  if (this->_value == 1  || tribool._value == 1)
    return (Tribool(1));
 if (this->_value == 2 || tribool._value == 2)
   return (Tribool(2));
 return (Tribool(0));
}

