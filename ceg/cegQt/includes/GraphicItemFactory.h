#ifndef GRAPHICITEMFACTORY_H
#define GRAPHICITEMFACTORY_H

#include <QGraphicsRectItem>

#include "AbstractBox.h"

class GraphicItemFactory
{
public:
    static QGraphicsRectItem * create(AbstractBox *);
};

#endif // GRAPHICITEMFACTORY_H
