// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyright (C) 2010 CEG development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Authors: CEG <ceg@ionlythink.com>, http://www.ionlythink.com
 */

#include "AbstractItem.h"
#include "Layer.h"
#include "ZoomAction.h" // debug

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
    case Qt::Key_Left :
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
	return (new ZoomAction(false));
	break;
    }
    return (0);
}
