#ifndef BACKWARD_CHAINING_H
# define BACKWARD_CHAINING_H

# include "RuleSet.h"
# include "FactSet.h"

int	resolve_fact(Fact* fact, RuleSet & ruleset, FactSet& knownfacts);
bool	resolve_rule(Rule rule, RuleSet & ruleset, FactSet& facts);
int	eval_expr(FactSet & facts);
#endif
