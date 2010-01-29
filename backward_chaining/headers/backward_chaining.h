#ifndef BACKWARD_CHAINING_H
# define BACKWARD_CHAINING_H

# include "RuleSet.h"
# include "FactSet.h"

Tribool	resolve_fact(Fact* fact, RuleSet & ruleset, FactSet& knownfacts);
Tribool	resolve_rule(Rule& rule, RuleSet & ruleset, FactSet& facts);
Tribool	eval_expr(FactSet & facts, Rule & rule);
Tribool eval_all(int *i, std::string proposition, FactSet& facts);
Tribool eval_unit(int *i, std::string& proposition,   FactSet & facts);
bool isCaps(char c);

#endif
