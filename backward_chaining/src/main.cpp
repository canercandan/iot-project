#include <iostream>
#include "Rule.h"

int	main(int ac, char **av)
{

  if (av[1] == NULL || ac != 2)
    {
      std::cerr << "usage: ./BackwardChaining RulesFile.txt"<< std::endl;
      return (1);
    }
  Rule rule1(std::string("R1"), std::string("A & B -> Z"));
  std::cout<< "ca rullezzz"<< std::endl;
  return 0;
}
