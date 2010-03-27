#ifndef LAYOUT_H
#define LAYOUT_H

#include <QGraphicsScene>

class Layout : public QGraphicsScene
{
public:
    Layout( qreal x, qreal y, qreal width, qreal height, QObject * parent = 0 );

    void keyPressEvent ( QKeyEvent * keyEvent );
};

#endif // LAYOUT_H
