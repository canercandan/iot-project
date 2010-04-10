#include <algorithm>

#include <QtGui/QApplication> // debug
#include <QDesktopWidget> // debug

#include "LayerManager.h"
#include "Layer.h" // debug
#include "Window.h" // debug

LayerManager::LayerManager() :
        _boxManager(new BoxManager)
{
    this->_view.setWindowOpacity(0.5);
}

LayerManager::~LayerManager()
{
    //std::for_each(this->_layers.begin(), this->_layers.end(), delete);
    delete this->_boxManager;
}

void LayerManager::init()
{
    QDesktopWidget *desktop = QApplication::desktop();
    Ceg::Window aWindow(0, WindowGeometry(0 , 0, desktop->width(), desktop->height()));


    Layer * oneLayer = new Layer(aWindow);
    std::list<QGraphicsRectItem *> list;
    this->_boxManager->getPattern("Desktop", aWindow, list);
    oneLayer->initScene(list);
    this->_layers.push_front(oneLayer);
    this->_currentLayer = this->_layers.begin();
}

void LayerManager::start()
{
    this->_view.setScene(*(this->_currentLayer));
    this->_view.setSceneRect((*(this->_currentLayer))->sceneRect());
    this->_view.show();
}
