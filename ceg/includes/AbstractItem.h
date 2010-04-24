#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QGraphicsRectItem>

#include "AbstractBox.h"
#include "IAction.h"

class AbstractItem : public QGraphicsRectItem
{
public:
    AbstractItem(AbstractBox * box, QGraphicsItem * parent = 0);

    IAction * onEvent();

protected:
    virtual void focusInEvent(QFocusEvent * event);
    virtual void focusOutEvent(QFocusEvent * event);
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

protected:
    Qt::GlobalColor _color;
    AbstractBox *   _box;
};

#endif // ABSTRACTITEM_H
