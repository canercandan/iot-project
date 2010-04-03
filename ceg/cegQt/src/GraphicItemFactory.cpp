#include "GraphicItemFactory.h"


QGraphicsRectItem * GraphicItemFactory::create(AbstractBox const *) const
{
    return (new QGraphicsRectItem);
}
