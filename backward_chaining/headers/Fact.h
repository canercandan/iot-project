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
  Fact(const char name, char value, bool isConst);
  ~Fact();

  void		display();

  const char	_name;
  char		_value;


private:
  bool		_isConst;
};

#endif /* !! FACT_H */
