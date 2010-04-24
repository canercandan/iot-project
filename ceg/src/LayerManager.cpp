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
  for (std::list<AbstractScene*>::iterator
	 it = this->_layers.begin(),
	 end = this->_layers.end();
       it != end; ++it)
    {
      delete *it;
    }

    delete this->_boxManager;
    delete this->_comGs;
}

void LayerManager::init()
{
    std::list<Ceg::Window>  windows;
    //this->_comGs->getWindows(windows);

    QDesktopWidget *desktop = QApplication::desktop();
    windows.push_back(Ceg::Window(0, WindowGeometry(0 , 0, desktop->width(), desktop->height())));

    this->createLayers(windows);
    this->_currentLayer = this->_layers.begin();
}

void LayerManager::start()
{
    this->_view.setScene(*(this->_currentLayer));
    WindowGeometry  geo = (*(this->_currentLayer))->getGeometry();
    this->_view.setGeometry(geo._x, geo._y, geo._width,geo._height);
    this->_view.show();
    //sleep(1);
    QCursor::setPos(100,100);
}

void LayerManager::createLayers(std::list<Ceg::Window> & windows)
{
    std::list<Ceg::Window>::iterator it = windows.begin();
    std::list<Ceg::Window>::iterator itEnd = windows.end();

    for (; it != itEnd; ++it)
    {
	Layer * oneLayer = new Layer(*it);
	std::list<QGraphicsRectItem *> graphicItems;
	this->_boxManager->getPattern("Desktop", *it, graphicItems);
	oneLayer->initScene(graphicItems);
	this->_layers.push_front(oneLayer);
    }
}
