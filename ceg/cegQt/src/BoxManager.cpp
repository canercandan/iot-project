#include "BoxManager.h"

BoxManager::BoxManager()
{
  this->loadConf();
}

BoxManager::loadConf()
{

  std::list<AbstractBox* >list1;
  std::cout<< sizeof(list1) << std::endl;
  this->_patterns.insert<std::string, std::list<AbstractBox*> >("OneConf", list1)
}
