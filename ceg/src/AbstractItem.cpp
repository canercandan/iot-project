#include <QPainter>

#include "AbstractItem.h"

AbstractItem::AbstractItem(AbstractBox * box, QGraphicsItem * parent) :
        QGraphicsRectItem(box->getGeometry()._x, box->getGeometry()._y, box->getGeometry()._width, box->getGeometry()._height, parent),
        _color(Qt::darkBlue), _box(box)
{
    this->setFlag(QGraphicsItem::ItemIsFocusable);
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
