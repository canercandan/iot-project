#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QGraphicsRectItem>

class AbstractItem : public QGraphicsRectItem
{
public:
    AbstractItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);

protected:
    virtual void focusInEvent(QFocusEvent * event);
    virtual void focusOutEvent(QFocusEvent * event);
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) ;

private:
    Qt::GlobalColor _color;
};

#endif // ABSTRACTITEM_H
