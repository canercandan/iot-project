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

/*********************************/
#include "Menu.h"
/*********************************/
#include "AbstractItem.h"
#include "Box.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

Menu::Menu()
    : AbstractScene(QRect(100, 100, 100, 100))
{
}

/************************************************* [ GETTERS ] *************************************************/

QRect  Menu::getGeometry() const
{
    QList<QGraphicsItem *> items =  this->items();
    QRect totalSize(0,0,0,0);
    for (QList<QGraphicsItem *>::const_iterator it = items.begin(), itEnd = items.end(); it != itEnd; ++it)
    {
	AbstractItem * item = static_cast<AbstractItem *>(*it);
	totalSize.united(item->getBox()->getGeometry());
    }
    return (totalSize);
}

/************************************************* [ OTHERS ] *************************************************/

IAction * Menu::keyPressEvent(int key) const
{
    switch (key)
    {
    case Qt::Key_Left :
    case Qt::Key_Right :
	this->moveHorizontally();
	break;
    case Qt::Key_Up :
    case Qt::Key_Down :
	this->moveVertically();
	break;
    case Qt::Key_Return :
	{
	    AbstractItem * focusItem = static_cast<AbstractItem *>(this->focusItem());
	    return (focusItem->getEvent());
	}
	break;
    default:
	break;
    }
    return (0);
}

void	Menu::moveVertically() const
{
    QList<QGraphicsItem *> items =  this->items();
    int sizeList = items.size();
    QGraphicsItem * focusItem = this->focusItem();
    QList<QGraphicsItem *>::const_iterator it = items.begin();
    QList<QGraphicsItem *>::const_iterator tmpIt = it;

    int index = items.indexOf(focusItem);
    ++index;
    QRectF currentRectF = focusItem->boundingRect();
    currentRectF.setHeight(this->getGeometry().height());
    currentRectF.setWidth(currentRectF.width());
    currentRectF.setX(currentRectF.x());
    currentRectF.setY(0);

    int i = 0;
    bool haveRect = false;
    while (i < sizeList && haveRect == false)
    {
	index = ((index < sizeList) ? index : (index - sizeList));
	tmpIt = it;
	tmpIt += index;
	haveRect = currentRectF.intersects((*tmpIt)->boundingRect());
	++index;
	++i;
    }
    if (haveRect == true)
    {
	(*tmpIt)->setFocus();
    }
    else
    {
	index = items.indexOf(focusItem) + 1;
	index = ((index < sizeList) ? index : (index - sizeList));
	it += index;
	(*it)->setFocus();
    }
}

void	Menu::moveHorizontally() const
{
    QList<QGraphicsItem *> items =  this->items();
    int index = items.indexOf(this->focusItem());
    ++index;
    if (index >= items.size())
    {
	index = 0;
    }
    QList<QGraphicsItem *>::const_iterator it = items.begin() + index;
    (*it)->setFocus();
}
