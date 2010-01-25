#ifndef PARSING_RESULT_H_
#define PARSING_RESULT_H_

#include <string>

struct	ParsingResult
{
  std::string	first;
  std::string	second;
  void	setFirst(const std::string& str) { first = str; }
  void	setSecond(const std::string& str) { second = str; }
};

#endif
