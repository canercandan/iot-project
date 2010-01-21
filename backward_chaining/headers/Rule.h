#ifndef RULE_H
# define RULE_H
# include <string>

class Rule
{
public:
  Rule(const std::string  name, std::string expr);
  ~Rule();
  
  const std::string _name; /*provisoirement public... ou pas :)*/
  std::string _expr;/* // */
  
private:
  ;
;

};

#endif
