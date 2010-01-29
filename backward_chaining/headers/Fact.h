#ifndef FACT_H
# define FACT_H

# include <string>
# include "IOper.h"
# include "Tribool.h"

class	Fact : public IOper
{
public:
  Fact(const char name, Tribool value, bool isConst);
  ~Fact();

  void		display();

  void		setValFromConclusion(std::string const & conclusion);

  const char	_name;
  Tribool	_value;
  bool		_isConst;
};

#endif /* !! FACT_H */
