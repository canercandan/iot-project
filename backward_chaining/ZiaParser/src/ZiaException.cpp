#include "ZiaException.h"
#include <iostream>

ZiaException::ZiaException(std::string error) throw() : _error(error)
{
  
}

ZiaException::~ZiaException() throw()
{
  
}

const char* ZiaException::what() const throw()
{
  return (this->_error.c_str());
}
