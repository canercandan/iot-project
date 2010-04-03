#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <list>

#include <QGraphicsView>

#include "AbstractScene.h"
#include "BoxManager.h"

class LayerManager
{
public:
    LayerManager();

    void    start();

private:
    QGraphicsView   _view;
    std::list<AbstractScene *>    _layers;
    std::list<AbstractScene *>::iterator    _currentLayer;
    BoxManager* _boxManager;
};

#endif // LAYERMANAGER_H
