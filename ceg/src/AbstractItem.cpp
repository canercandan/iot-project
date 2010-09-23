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
#include <QPainter>
/*********************************/
#include "AbstractItem.h"
/*********************************/
#include "Box.h"
#include "ZoomAction.h"
#include "ClickAction.h"
#include "Logger.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

AbstractItem::AbstractItem(Box const * box, QGraphicsItem * parent) :
	QGraphicsRectItem(box->getGeometry().x(), box->getGeometry().y(), box->getGeometry().width(), box->getGeometry().height(), parent),
	_color(box->getGraphicStyle().getBlurColor()), _model(box)
{
    this->setFlags(QGraphicsItem::ItemIsFocusable);
}

/************************************************* [ GETTERS ] *************************************************/

Box const * AbstractItem::getBox() const
{
    return (this->_model);
}

IAction * AbstractItem::getEvent() const
{
    return (this->_model->getAction());
}

/************************************************* [ OTHERS ] *************************************************/

void AbstractItem::focusInEvent(QFocusEvent *)
{
    this->_color = this->_model->getGraphicStyle().getFocusColor();
    this->update();
}

void AbstractItem::focusOutEvent(QFocusEvent *)
{
    this->_color = this->_model->getGraphicStyle().getBlurColor();
    this->update();
}
#include <QDebug>
void AbstractItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    BoxStyle const & style = _model->getGraphicStyle();
	painter->setOpacity(style.getOpacity());
    painter->setBrush(QBrush(QColor(this->_color)));
    //painter->drawRect(this->rect());
    if (style.isRounded())
        painter->drawRoundedRect(this->rect(), 15, 15);
    else
        painter->drawRect(this->rect());
    qDebug() << "Draw rect = " << this->rect() << " - " << this->_model->getGeometry();
    QString const & text = style.getText();
    if (! text.isEmpty()) // ici
    {
	QString const & textFont = style.getTextFont();

	if (textFont.isEmpty() == false)
	{
	    painter->setFont(QFont(textFont, style.getTextFontSize()));
	}

	QString const & textColor = style.getTextColor();
	if (textColor.isEmpty() == false)
	{
	    painter->setPen(textColor);
	}

        QString const & imagePath  = style.getImagePath();
        if (imagePath.isEmpty() == false)
        {
            QPixmap pixmap(imagePath);
            QRectF dest(this->rect().x(), this->rect().y(), pixmap.width(), pixmap.height());
            dest.moveCenter(this->rect().center());
            painter->drawPixmap(dest, pixmap, pixmap.rect());
            painter->drawText(this->rect(), Qt::AlignBottom|Qt::AlignCenter, text);
        }
	else
	{
            painter->drawText(this->rect(), Qt::AlignCenter, text);
	}
  }
}
