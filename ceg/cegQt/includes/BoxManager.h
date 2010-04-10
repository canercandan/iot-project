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

    void getPattern(std::string const &, Ceg::Window const &, std::list<QGraphicsRectItem *> & list);
    /*
    ** load les configurations xml dans _patterns
    */
    void	loadConf();

private:
    void    getDefaultPattern(std::list<QGraphicsRectItem *> &, const Ceg::Window &);

private:
    std::map<std::string, std::list<AbstractBox *> > _patterns;
};

#endif // BOXMANAGER_H
