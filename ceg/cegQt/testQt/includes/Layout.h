#ifndef LAYOUT_H
#define LAYOUT_H

#include <QGraphicsScene>

class Layout : public QGraphicsScene
{
public:
    Layout( qreal x, qreal y, qreal width, qreal height, QObject * parent = 0 );

    void    drawGrid(qreal width, qreal height, qreal posX = 0, qreal posY = 0);
    void    drawChild(QGraphicsItem * item);
    bool    drawParent(QGraphicsItem * item);

    void keyPressEvent ( QKeyEvent * keyEvent );

private:
    void clearLayout();
};

#endif // LAYOUT_H
