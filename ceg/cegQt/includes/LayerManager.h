#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <list>

#include <QGraphicsView>

#include "AbstractScene.h"

class LayerManager
{
public:
    LayerManager();

private:
    QGraphicsView   _view;
    std::list<AbstractScene>    _layers;
    std::list<AbstractScene>::iterator    _currentLayer;
};

#endif // LAYERMANAGER_H
