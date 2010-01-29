#ifndef BACKWARD_CHAINING_H
# define BACKWARD_CHAINING_H

# include "RuleSet.h"
# include "FactSet.h"

Tribool	resolve_fact(Fact* fact, RuleSet & ruleset, FactSet& knownfacts);
Tribool	resolve_rule(Rule& rule, RuleSet & ruleset, FactSet& facts, char searchFactName);
bool	isCaps(char c);

#endif
