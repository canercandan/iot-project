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

#include <iostream>

#include <QMessageBox>

#include "MyAweSomeBox.h"

MyAweSomeBox::MyAweSomeBox( qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent) :
		QGraphicsRectItem(x, y, width, height, parent), _color(Qt::darkBlue)
{
	this->setFlag(QGraphicsItem::ItemIsFocusable);
}


void MyAweSomeBox::focusInEvent( QFocusEvent *)
{
	this->_color = Qt::yellow;
	this->update();
}

void MyAweSomeBox::focusOutEvent( QFocusEvent *)
{
	this->_color = Qt::darkBlue;
	this->update();
}

void MyAweSomeBox::mousePressEvent(QGraphicsSceneMouseEvent *)
{
	this->_color = Qt::yellow;
	this->setFocus();
	this->update();
}

void MyAweSomeBox::paint ( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setBrush(this->_color);
	painter->drawRect(this->rect());
}

bool MyAweSomeBox::sceneEvent ( QEvent * event )
{
	//std::cout << "MyAweSomeBox::sceneEvent == " << event->type() << std::endl;
	return (QGraphicsItem::sceneEvent (event ));
}
