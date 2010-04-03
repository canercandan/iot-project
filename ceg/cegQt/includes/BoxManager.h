#ifndef BOXMANAGER_H
#define BOXMANAGER_H

#include <map>
#include <list>
#include <string>

#include <QGraphicsRectItem>

#include "AbstractBox.h"
#include "Window.h"

class BoxManager
{
public:
    BoxManager();

    std::list<QGraphicsRectItem *> & getPattern(std::string const &, Ceg::Window const &);
    /*
    ** load les configurations xml dans _patterns
    */
    void	loadConf();

private:
    std::map<std::string, std::list<AbstractBox *> > _patterns;
};

#endif // BOXMANAGER_H
