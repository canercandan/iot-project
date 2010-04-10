#include <algorithm>

#include <QtGui/QApplication> // debug
#include <QDesktopWidget> // debug

#include "LayerManager.h"
#include "Layer.h" // debug
#include "Window.h" // debug

#ifdef _WIN32
#include "Win32Explorer.h"
#else
#include "XWindowSystem.h"
#endif

LayerManager::LayerManager() :
        _boxManager(new BoxManager),
#ifdef _WIN32
        _comGs(new Win32Explorer)
#else
        _comGs(new XWindowSystem)
#endif
{
    this->_view.setWindowOpacity(0.5);
}

LayerManager::~LayerManager()
{
    //std::for_each(this->_layers.begin(), this->_layers.end(), delete);
    delete this->_boxManager;
    delete this->_comGs;
}

void LayerManager::init()
{
    /*std::list<Ceg::Window>  windows;
    this->_comGs->getWindows(windows);

    QDesktopWidget *desktop = QApplication::desktop();
    windows.push_back(Ceg::Window(0, WindowGeometry(0 , 0, desktop->width(), desktop->height())));


    Layer * oneLayer = new Layer(aWindow);
    std::list<QGraphicsRectItem *> list;
    this->_boxManager->getPattern("Desktop", aWindow, list);
    oneLayer->initScene(list);
    this->_layers.push_front(oneLayer);
    this->_currentLayer = this->_layers.begin();*/
}

void LayerManager::start()
{
    this->_view.setScene(*(this->_currentLayer));
    //this->_view.setGeometry((*(this->_currentLayer))->sceneRect());
    QDesktopWidget *desktop = QApplication::desktop();
    this->_view.setGeometry(0 , 0, desktop->width(), desktop->height());
    this->_view.show();
}
