#ifndef EVAL_H
# define EVAL_H

#include "Tribool.h"
#include "FactSet.h"
#include "Rule.h"

Tribool	eval_expr(FactSet & facts, Rule & rule);
Tribool	eval_all(int *i, std::string proposition, FactSet& facts);
Tribool	eval_unit(int *i, std::string& proposition, FactSet & facts);
bool	isCaps(char c);

#endif
