#ifndef RULESET
# define RULESET

#include <vector>
#include "Rule.h"
#include "Fact.h"

class RuleSet
{
 public:
  RuleSet(std::vector<Rule *>& ruleset);
  ~RuleSet();

  int	concludingRule(Fact const & fact) const;
  //Rule	getConcludingRule(Fact const & fact) const;
  //private:
   std::vector<Rule *> _ruleset;

};
#endif
