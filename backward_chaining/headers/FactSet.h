#ifndef FACTSET_H
# define FACTSET_H

# include <vector>
# include "Fact.h"

class	FactSet
{
 public:
  FactSet(std::vector<Fact *> facts);
  ~FactSet();
  void	add(Fact *fact);
  void	remove(Fact* fact);
  bool	exist(Fact *fact);
  Fact*	selectFact();
  /*retourne le fact au name correspondant*/
  Fact*	getFactByName(Fact * fact);

  void	display();
  Fact*	operator[](int	i);
  int	size();
private:
  std::vector<Fact *> _facts;
};

#endif /* !!FACTSET_H */
