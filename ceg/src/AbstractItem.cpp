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

#include <QPainter>

#include "AbstractItem.h"

AbstractItem::AbstractItem(AbstractBox * box, QGraphicsItem * parent) :
	QGraphicsRectItem(box->getGeometry()._x, box->getGeometry()._y, box->getGeometry()._width, box->getGeometry()._height, parent),
	_color(Qt::darkBlue), _box(box)
{
    this->setFlag(QGraphicsItem::ItemIsFocusable);
}

AbstractBox * AbstractItem::getBox() const
{
    return (this->_box);
}

IAction * AbstractItem::onEvent()
{
    return (0);
}

void AbstractItem::focusInEvent(QFocusEvent *)
{
    this->_color = Qt::yellow;
    this->update();
}

void AbstractItem::focusOutEvent(QFocusEvent *)
{
    this->_color = Qt::darkBlue;
    this->update();
}

void AbstractItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(this->_color);
    painter->drawRect(this->rect());
}
