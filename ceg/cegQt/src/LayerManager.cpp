#include <QDesktopWidget> // debug

#include "LayerManager.h"
#include "Layer.h" // debug
#include "Window.h" // debug

LayerManager::LayerManager() :
        _boxManager(new BoxManager)
{
    QDesktopWidget *desktop = QApplication::desktop();
    Ceg::Window aWindow(0, WindowGeometry(0 , 0, desktop->width(), desktop->height() - 100));
    Layer * oneLayer = new Layer(aWindow);

//    Layout scene(0, 0, desktop->width(), desktop->height() - 100);

    this->_view.setWindowOpacity(0.5);
}

void LayerManager::start()
{
    this->_view.setScene(oneLayer);
    this->_view.show();
}
