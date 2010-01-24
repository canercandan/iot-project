#include "Fact.h"


Fact::Fact(const char name, char value, bool isConst)
  : _name(name), _value(value), _isConst(isConst) /*les const sont ceux de la base initiale*/
{
}

Fact::~Fact()
{
}
