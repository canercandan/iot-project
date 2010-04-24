#include "Layer.h"
#include "AbstractItem.h"

Layer::Layer(Ceg::Window const & hostWindow) :
	AbstractScene(hostWindow.getGeometry()._x, hostWindow.getGeometry()._y, hostWindow.getGeometry()._width, hostWindow.getGeometry()._height),
	_host(hostWindow)
{
}

WindowGeometry  Layer::getGeometry() const
{
    return (this->_host.getGeometry());
}

IAction * Layer::keyPressEvent(int key)
{
    QList<QGraphicsItem *> items =  this->items();
    int sizeList = items.size();
    switch (key)
    {
    case Qt::Key_Left:
    case Qt::Key_Right :
	{
	    QGraphicsItem * focusItem = this->focusItem();
	    int index = items.indexOf(focusItem) + 1;
	    QList<QGraphicsItem *>::iterator it = items.begin();
	    if (index < sizeList)
		it += index;
	    (*it)->setFocus();
	}
	break;
    case Qt::Key_Up :
    case Qt::Key_Down:
	{
	    QGraphicsItem * focusItem = this->focusItem();
	    int index = items.indexOf(focusItem) + 3;
	    QList<QGraphicsItem *>::iterator it = items.begin();
	    it += ((index < sizeList) ? index : (index - sizeList));
	    (*it)->setFocus();
	}
	break;
    case Qt::Key_Return :
	{
	    AbstractItem * focusItem = static_cast<AbstractItem *>(this->focusItem());
	    return (focusItem->onEvent());
	}
	break;
    case Qt::Key_Backspace :
	//	this->drawParent(this->focusItem());
	break;
    }
    return (0);
}
