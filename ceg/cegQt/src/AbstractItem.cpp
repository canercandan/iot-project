#include "AbstractItem.h"

AbstractItem::AbstractItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0) :
        QGraphicsRectItem(x, y, width, height, parent), _color(Qt::darkBlue)
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
