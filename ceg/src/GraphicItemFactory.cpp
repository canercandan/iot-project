#include "GraphicItemFactory.h"
#include "DefaultItem.h"


QGraphicsRectItem * GraphicItemFactory::create(AbstractBox * box)
{
    return (new DefaultItem(box, 0));
}
