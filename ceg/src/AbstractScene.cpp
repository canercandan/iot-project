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

#include <QKeyEvent>

#include "AbstractScene.h"

AbstractScene::AbstractScene(qreal x, qreal y, qreal width, qreal height, QObject * parent) :
	QGraphicsScene(x, y, width, height, parent)
{
}

void AbstractScene::initScene(std::list<QGraphicsRectItem *> &newScene)
{
    this->clearScene();
    std::list<QGraphicsRectItem *>::const_iterator  it = newScene.begin();
    std::list<QGraphicsRectItem *>::const_iterator  itEnd = newScene.end();

    for (; it != itEnd; ++it)
    {
	this->addItem(*it);
    }
    newScene.front()->setFocus();
}

void AbstractScene::clearScene()
{
    QList<QGraphicsItem *> items = this->items();
    QList<QGraphicsItem *>::iterator it = items.begin();
    for (; it != items.end();)
    {
	QList<QGraphicsItem *>::iterator itTemp = it;
	++itTemp;
	QGraphicsItem * tmpItem = *it;
	this->removeItem(tmpItem);
	delete tmpItem;
	it = itTemp;
    }
}
