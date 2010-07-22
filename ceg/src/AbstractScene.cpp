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
#include <QDebug>
/*********************************/
#include "AbstractScene.h"
/*********************************/
#include "AbstractItem.h"
#include "Logger.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

AbstractScene::AbstractScene(QObject * parent /* = 0 */) :
        QGraphicsScene(parent), _type(DEFAULT_BOX), _focusItem(0)
{
}

AbstractScene::~AbstractScene()
{
    qDebug() << "AbstractScene::~AbstractScene()";
}

/************************************************* [ GETTERS ] *************************************************/

AbstractItem const *	AbstractScene::getCurrentItem() const
{
#if defined(Q_OS_WIN)
    return (this->_focusItem);
#else
    return (static_cast<AbstractItem *>(this->focusItem()));
#endif
}

BoxType AbstractScene::getType() const
{
    return (this->_type);
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
    QString msg("AbstractScene::initialize - ");
    QVariant size(static_cast<unsigned int>(sceneItems.size()));
    msg += size.toString();
    msg.append("items a ajoute a la scene");
    Logger::getInstance()->log(INFO_LOG, msg);
    this->clearScene();
    std::for_each(sceneItems.rbegin(), sceneItems.rend(), std::bind1st(std::mem_fun(&QGraphicsScene::addItem), this));
    sceneItems.front()->setFocus();
}

void AbstractScene::saveFocusItem()
{
    this->_focusItem = static_cast<AbstractItem *>(this->focusItem());
}

void AbstractScene::resetFocusItem()
{
    this->setFocusItem(this->_focusItem);
}
