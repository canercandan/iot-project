#ifndef GRAPHICITEMFACTORY_H
#define GRAPHICITEMFACTORY_H

#include <QGraphicsRectItem>

#include "AbstractBox.h"

class GraphicItemFactory
{
public:
    static QGraphicsRectItem * create(AbstractBox const *) const;
};

#endif // GRAPHICITEMFACTORY_H
