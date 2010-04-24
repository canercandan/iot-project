#include <iostream>

#include "GraphicItemFactory.h"
#include "BoxManager.h"

BoxManager::BoxManager()
{
    this->loadConf();
}

void    BoxManager::getPattern(std::string const & programName, const Ceg::Window & aWindow, std::list<QGraphicsRectItem *> & list)
{
    std::map<std::string, std::list<AbstractBox *> >::iterator  itFind = this->_patterns.find(programName);
    if (itFind != this->_patterns.end())
    {
        std::list<AbstractBox *>::iterator  it = itFind->second.begin();
        std::list<AbstractBox *>::iterator  itEnd = itFind->second.end();
        for (; it != itEnd; ++it)
        {
            list.push_back(GraphicItemFactory::create(*it));
        }
    }
    else
    {
        this->getDefaultPattern(list, aWindow);
    }
}

void BoxManager::getDefaultPattern(std::list<QGraphicsRectItem *> & list, const Ceg::Window & aWindow)
{
    WindowGeometry const & geo = aWindow.getGeometry();
    int nbGrid = 3;
    int tmpWidth = geo._width / nbGrid;
    int tmpHeight = geo._height / nbGrid;
    int rows = 0;
    int y = geo._y;
    while (rows++ < nbGrid)
    {
        int cols = 0;
        qreal x = geo._x;
        while (cols++ < nbGrid)
        {
            list.push_back(GraphicItemFactory::create(new AbstractBox(DEFAULT, 0, std::list<AbstractBox*>(0), WindowGeometry(x, y, tmpWidth, tmpHeight))));
            x += tmpWidth;
        }
        y += tmpHeight;
    }
}

void    BoxManager::loadConf()
{
    std::list<AbstractBox*> list1;
    std::cout<< sizeof(list1) << std::endl;
    list1.push_back(new AbstractBox(DEFAULT, 0, std::list<AbstractBox*>(0), WindowGeometry(10, 10, 10, 10)));
    list1.push_back(new AbstractBox(DEFAULT, 0, std::list<AbstractBox*>(0), WindowGeometry(50, 50, 50, 50)));
}

