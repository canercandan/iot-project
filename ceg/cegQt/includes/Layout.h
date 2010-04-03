#ifndef LAYOUT_H
#define LAYOUT_H

#include <QGraphicsScene>

class Layout : public QGraphicsScene
{
public:
    Layout( qreal x, qreal y, qreal width, qreal height, QObject * parent = 0 );

    void    drawGrid(QGraphicsScene & scene, int width, int height, int posX = 0, int posY = 0);
    void    drawChild(QGraphicsScene & scene, QGraphicsRectItem & item);
    bool    drawParent(QGraphicsScene & scene, int posX, int posY, int width);

    void keyPressEvent (QKeyEvent * keyEvent);
};

#endif // LAYOUT_H
