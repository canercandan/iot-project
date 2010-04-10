#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <list>

#include <QGraphicsView>

#include "AbstractScene.h"
#include "BoxManager.h"
#include "ICommunicationGraphicalServer.h"

class LayerManager
{
public:
    LayerManager();
    ~LayerManager();

    void    init();
    void    start();

private:
    QGraphicsView   _view;
    std::list<AbstractScene *>    _layers;
    std::list<AbstractScene *>::iterator    _currentLayer;
    BoxManager* _boxManager;
    ICommunicationGraphicalServer * _comGs;
};

#endif // LAYERMANAGER_H
