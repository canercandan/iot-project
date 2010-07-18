
// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyleft (C) 2010 CEG development team
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
#include <QDebug>
#include <QMessageBox>
/*********************************/
#include "AbstractItem.h"
/*********************************/
#include "Layer.h"
/*********************************/
#include "Box.h"
#include "PopMenuAction.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

Layer::Layer(Ceg::Window const & hostWindow) :
	AbstractScene(0), _host(hostWindow), _menuAction(0)
{
}

Layer::~Layer()
{
    delete this->_menuAction;
}

/************************************************* [ GETTERS ] *************************************************/

QRect  Layer::getGeometry() const
{
    return (this->_host.getGeometry());
}

/************************************************* [ OTHERS ] *************************************************/

void	Layer::initialize(std::list<QGraphicsRectItem *> const & sceneItems)
{
    if (sceneItems.empty() == false)
    {
	AbstractItem const * firstItem = static_cast<AbstractItem const *>(sceneItems.front());
        if (firstItem->getBox()->getBoxType() == DEFAULT_BOX && this->_menuAction == 0)
	{
            this->_menuAction = new PopMenuAction("Navigation");
	}
    }
    AbstractScene::initialize(sceneItems);
}

IAction * Layer::keyPressEvent(int key) const
{
    switch (key)
    {
    case Qt::Key_Left :
    case Qt::Key_Right :
	return (this->moveHorizontally());
	break;
    case Qt::Key_Up :
    case Qt::Key_Down :
	return (this->moveVertically());
	break;
    default:
	break;
    }
    return (0);
}

IAction *	Layer::moveVertically() const
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
    return (0);
}

IAction *	Layer::moveHorizontally() const
{
    QList<QGraphicsItem *> items =  this->items();
    QList<QGraphicsItem *>::const_iterator it = items.begin();
    QGraphicsItem * focusItem = this->focusItem();
    int index = items.indexOf(focusItem);
    index++;
    if (index >= items.size())
    {
	index = 0;
    }
    it += index;
    (*it)->setFocus();
    if (focusItem->boundingRect().x() > (*it)->boundingRect().x())
    {
	return (this->_menuAction);
    }
    return (0);
}
