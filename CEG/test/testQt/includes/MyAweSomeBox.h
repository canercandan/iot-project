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

#ifndef MYAWESOMEBOX_H
#define MYAWESOMEBOX_H

#include <QColor>
#include <QGraphicsWidget>
#include <QGraphicsRectItem>
#include <QPainter>


class MyAweSomeBox : public QGraphicsRectItem
{
public:
    MyAweSomeBox( qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0 );

protected:
    void focusInEvent( QFocusEvent * event );
    void focusOutEvent( QFocusEvent * event );
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 ) ;
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    bool sceneEvent (QEvent * event);

private:
    Qt::GlobalColor _color;
};

#endif // MYAWESOMEBOX_H
