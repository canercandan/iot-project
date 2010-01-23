#ifndef RULE_H
# define RULE_H
# include <string>

class Rule
{
public:
  Rule(const std::string  name, const std::string condition, const std::string implication);
  ~Rule();
  bool isBurned() const;
  std::string const & getImplication() const;
  void	burn();

 private:
  const std::string _name;
  const std::string _condition;
  const std::string _implication;
  bool	_burned;
};

#endif
