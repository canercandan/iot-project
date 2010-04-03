#include <iostream>

#include "BoxManager.h"

BoxManager::BoxManager()
{
  this->loadConf();
}

std::list<QGraphicsRectItem *> &    BoxManager::getPattern(std::string const & programName, const Ceg::Window & aWindow)
{
    std::list<QGraphicsRectItem *> * list = new std::list<QGraphicsRectItem *>;
    std::map<std::string, std::list<AbstractBox *> >::iterator  itFind = this->_patterns.find(programName);
    if (itFind != this->_patterns.end())
    {
        list = 0;
    }
    return (*list);
}

void    BoxManager::loadConf()
{
  std::list<AbstractBox*> list1;
  std::cout<< sizeof(list1) << std::endl;
  //  list1.push_back(new AbstractBox(DEFAULT, 0, 0, WindowGeometry()));
  this->_patterns.insert(std::pair<std::string, std::list<AbstractBox*> >("OneConf", list1));

  
}

