#ifndef DEFAULTITEM_H
#define DEFAULTITEM_H

#include "AbstractItem.h"

class DefaultItem : public AbstractItem
{
public:
    DefaultItem(AbstractBox * box, QGraphicsItem * parent = 0);
   ~DefaultItem();

protected:
    void keyPressEvent(QKeyEvent * event);
};

#endif // DEFAULTITEM_H
