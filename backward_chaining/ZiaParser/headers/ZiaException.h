#ifndef ZIA_EXCEPTION_H
# define ZIA_EXCEPTION_H

# include <exception>
# include <string>

class	ZiaException : public std::exception
{
 public:
  ZiaException(std::string error) throw();
  ~ZiaException() throw();
  virtual const char* what() const throw();
private:
  std::string _error;
};
#endif /* ZIA_EXCEPTION_H */
