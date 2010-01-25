#ifndef BACKWARD_CHAINING_H
# define BACKWARD_CHAINING_H

# include "RuleSet.h"
# include "FactSet.h"

int	resolve_fact(Fact* fact, RuleSet & ruleset, FactSet& knownfacts);
bool	fire_ability(Rule rule, RuleSet & ruleset, FactSet& facts);

#endif
