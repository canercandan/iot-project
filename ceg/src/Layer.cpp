#include "Layer.h"

Layer::Layer(Ceg::Window const & hostWindow) :
	AbstractScene(hostWindow.getGeometry()._x, hostWindow.getGeometry()._y, hostWindow.getGeometry()._width, hostWindow.getGeometry()._height),
	_host(hostWindow)
{
}

WindowGeometry  Layer::getGeometry() const
 {
    return (this->_host.getGeometry());
 }
