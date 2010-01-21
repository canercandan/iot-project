#ifndef FACT_H
# define FACT_H

# define TRUE 1
# define FALSE 0
# define UNDEF 2

# include <string>

class	Fact
{
 public:
  Fact(const std::string name, char value);
  ~Fact();
  const std::string _name;
  char _value;
  ;
 private: 
   ;
};

#endif // !! FACT_H
