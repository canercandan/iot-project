#include "DefaultItem.h"

DefaultItem::DefaultItem(AbstractBox * box, QGraphicsItem * parent) :
        AbstractItem(box, parent)
{
}

void DefaultItem::keyPressEvent(QKeyEvent *) // a implementer
{
}
