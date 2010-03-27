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
    bool sceneEvent ( QEvent * event );

private:
    Qt::GlobalColor _color;
};

#endif // MYAWESOMEBOX_H
