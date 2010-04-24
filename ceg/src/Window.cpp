#include "Window.h"

namespace Ceg
{
    Window::Window() :
            _id(0), _geometry(), _isVisible(false)
    {

    }

    Window::Window(WindowId windowId, WindowGeometry const & windoInfo, bool visibility) :
            _id(windowId), _geometry(windoInfo), _isVisible(visibility)
    {
    }

    WindowId Window::getId() const
    {
        return (this->_id);
    }

    WindowGeometry const & Window::getGeometry() const
    {
        return (this->_geometry);
    }

    void Window::setId(WindowId id)
    {
        this->_id = id;
    }

    void Window::setCharacteristic(WindowGeometry const & rhs)
    {
        this->_geometry = rhs;
    }
}
