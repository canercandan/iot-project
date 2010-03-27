#include <iostream>

#include <QKeyEvent>
 #include <QList>
#include <QGraphicsItem>

#include "Layout.h"

Layout::Layout( qreal x, qreal y, qreal width, qreal height, QObject * parent) :
        QGraphicsScene(x, y, width, height, parent)
{
}

void Layout::keyPressEvent ( QKeyEvent * keyEvent )
{
    std::cout << "Layout::keyPressEvent = " << keyEvent->key() << std::endl;
    QList<QGraphicsItem *> items =  this->items();
    switch (keyEvent->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right :
        QGraphicsItem * focusItem = this->focusItem();
        int index = items.indexOf(focusItem) + 1;
        QList<QGraphicsItem *>::iterator it = items.begin();
        it += index;
        (*it)->setFocus();

        //focusItem->setFocus();
        break;/*
        case Qt::Key_Up :
        case Qt::Key_Down:
        break;
    }*/
    }
}
