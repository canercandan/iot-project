#ifndef DEFAULTITEM_H
#define DEFAULTITEM_H

#include "AbstractItem.h"

class DefaultItem : public AbstractItem
{
public:
    DefaultItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);

protected:
    void keyPressEvent(QKeyEvent * event);
};

#endif // DEFAULTITEM_H
