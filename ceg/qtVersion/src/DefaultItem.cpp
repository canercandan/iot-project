#include "DefaultItem.h"

DefaultItem::DefaultItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0) :
        QGraphicsRectItem(x, y, width, height, parent)
{
}

void DefaultItem::keyPressEvent(QKeyEvent *) // a implementer
{
}
