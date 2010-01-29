#ifndef FACT_H
# define FACT_H

# define TRUE 1
# define FALSE 0
# define UNDEF 2

# include <string>
# include "IOper.h"

class	Fact : public IOper
{
public:
  Fact(const char name, int value, bool isConst);
  ~Fact();

  void		display();

  const char	_name;
  int		_value;
  bool		_isConst;
};

#endif /* !! FACT_H */
