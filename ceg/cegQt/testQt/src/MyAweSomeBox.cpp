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