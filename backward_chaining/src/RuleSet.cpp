#include "RuleSet.h"


RuleSet::RuleSet(std::vector<Rule *>& ruleset)
  : _ruleset(ruleset)
{
}

RuleSet::~RuleSet()
{
}

//retourne la meilleure regle a analyser ou -1
int	RuleSet::concludingRule(Fact const &fact) const
{
  Rule* cur;
  int max = this->_ruleset.size();
  for (int i = 0; i < max; ++i)
    {
      cur = this->_ruleset[i];
      //si regle pas brulee
	if (cur->isBurned() == false)
	  {
	    // chercher si dans l'implication le fact est compris
	    // dans un permier temps de maniere simple chercher juste la lettre
	    std::string conclusion = cur->getConclusion();
	    for (int j = 0; j < conclusion.size(); ++j)
	      {
		if (conclusion[j] == fact._name)
		  return (i);
	      }
	  }
    }
  return -1;
}
