#include "DefaultItem.h"

DefaultItem::DefaultItem(AbstractBox * box, QGraphicsItem * parent) :
        AbstractItem(box, parent)
{
}

DefaultItem::~DefaultItem()
{
  delete _box;
}

void DefaultItem::keyPressEvent(QKeyEvent *) // a implementer
{
}
