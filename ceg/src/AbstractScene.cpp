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
#include <QTextStream>
/*********************************/
#include "AbstractScene.h"
/*********************************/
#include "AbstractItem.h"
#include "Logger.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

AbstractScene::AbstractScene(QString const & id, QObject * parent /* = 0 */) :
        QGraphicsScene(parent), _type(DEFAULT_BOX), _id(id)
{
}

bool    AbstractScene::operator ==(QString const & id) const
{
    return (id == this->_id);
}

bool    AbstractScene::operator ==(BoxType const & type) const
{
    return (type == this->_type);
}

/************************************************* [ GETTERS ] *************************************************/

AbstractItem const *	AbstractScene::getCurrentItem() const
{
    return (static_cast<AbstractItem *>(this->focusItem()));
}

BoxType AbstractScene::getType() const
{
    return (this->_type);
}

/************************************************* [ OTHERS ] *************************************************/

void    AbstractScene::resetFocusItem()
{
    this->setFocusItem(this->items().front());
}

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
void AbstractScene::initialize(QList<QGraphicsRectItem *> const & sceneItems)
{
    QString msg;
    QTextStream tmp(&msg);
    tmp << "AbstractScene::initialize - " << sceneItems.size() << " items a ajoute a la scene";
    Logger::getInstance()->log(INFO_LOG, msg);

    this->clearScene();
    QList<QGraphicsRectItem *>::const_iterator    it = sceneItems.end(), itEnd = sceneItems.begin();
    // Sous les versions anterieures a 4.6, la methode addItem effectue un push_back et dans les versions superieures un push_front d'ou le parcours inverse de la liste
    while (it != itEnd)
    {
        --it;
        this->addItem(*it);
    }
    this->setFocusItem(this->items().front());
}
