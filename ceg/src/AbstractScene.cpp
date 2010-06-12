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
#include <functional>
#include <algorithm>
/*********************************/
#include "AbstractScene.h"
/*********************************/
#include "AbstractItem.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

AbstractScene::AbstractScene(QRect const & geometry, QObject * parent /* = 0 */) :
	QGraphicsScene(geometry.x(), geometry.y(), geometry.width(), geometry.height(), parent)
{
}

/************************************************* [ GETTERS ] *************************************************/

AbstractItem const *	AbstractScene::getCurrentItem() const
{
    return (static_cast<AbstractItem *>(this->focusItem()));
}

/************************************************* [ OTHERS ] *************************************************/

void AbstractScene::clearScene()
{
    QList<QGraphicsItem *> items = this->items();
    for (QList<QGraphicsItem *>::iterator it = items.begin(); it != items.end();)
    {
	QGraphicsItem * tmpItem = *it;
	++it;
	this->removeItem(tmpItem);
	delete tmpItem;
    }
}

//! takes a scene (a list of Items) to draw graphical areas on the view
// Sous les versions anterieures a 4.6, la methode addItem effectue un push_back et dans les versions superieures un push_front d'ou le rbegin et rend
// la liste de nos items etant deja triee.
void AbstractScene::initialize(std::list<QGraphicsRectItem *> const & sceneItems)
{
    this->clearScene();
#if (QT_VERSION < QT_VERSION_CHECK(4,6,0))
    std::for_each(sceneItems.begin(), sceneItems.end(), std::bind1st(std::mem_fun(&QGraphicsScene::addItem), this));
#else
    std::for_each(sceneItems.rbegin(), sceneItems.rend(), std::bind1st(std::mem_fun(&QGraphicsScene::addItem), this));
#endif
    sceneItems.front()->setFocus();
}
