#ifndef RULE_H
# define RULE_H
# include <string>
# include <vector>
# include  "FactSet.h"

class Rule
{
public:
  Rule(const std::string  name, const std::string proposition, const std::string conclusion);
  ~Rule();
  bool isBurned() const;
  std::string const & getConclusion() const;
  std::string const & getProposition() const;
  void		burn();
  FactSet	getFactFromProposition();
  std::string const & getName() const;

private:
  const std::string	_name;
  const std::string	_proposition;
  const std::string	_conclusion;
  bool			_burned;
};

#endif /* !RULE_H */
