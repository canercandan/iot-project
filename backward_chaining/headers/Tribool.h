#ifndef TRIBOOL_H
# define TRIBOOL_H

#include <iostream>

class	Tribool
{
 public:

  Tribool(int value);
  ~Tribool();
  int	_value;
  friend std::ostream &  operator<<(std::ostream & os, Tribool& tribool);

  Tribool operator == (Tribool  tribool);
  Tribool operator & (Tribool  tribool);
  Tribool operator | (Tribool  tribool);
}
;

#endif
