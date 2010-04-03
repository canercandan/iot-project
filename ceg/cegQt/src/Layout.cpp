#include <iostream>

#include <QKeyEvent>
#include <QList>
#include <QGraphicsItem>

#include "Layout.h"

Layout::Layout( qreal x, qreal y, qreal width, qreal height, QObject * parent) :
        QGraphicsScene(x, y, width, height, parent)
{
    drawGrid(scene, WinWidth, WinHeight);
    QList<QGraphicsItem *> items =  scene.items ();
    items.first()->setFocus();
}

void    Layout::drawGrid(QGraphicsScene & scene, int width, int height, int posX = 0, int posY = 0)
{
    int nbGrid = 3;
    int tmpWidth = width / nbGrid;
    int tmpHeight = height / nbGrid;
    int rows = 0;
    while (rows++ < nbGrid)
    {
        int cols = 0;
        while (cols++ < nbGrid)
        {
            scene.addItem(new MyAweSomeBox(posX, posY, tmpWidth, tmpHeight));
            posX += tmpWidth;
        }
        posX = 0;
        posY += tmpHeight;
    }
}

void    Layout::drawChild(QGraphicsScene & scene, QGraphicsRectItem & item)
{
    drawGrid(scene, item.rect().width(), item.rect().height(), item.rect().x(), item.rect().y());
}

bool    Layout::drawParent(QGraphicsScene & scene, int posX, int posY, int width)
{
    int level = (QApplication::desktop()->width() / width) - 1;
    if (!level)
    {
        return (false);
    }
    QDesktopWidget *desktop = QApplication::desktop();
    int Width = desktop->width() / level;
    int Height = desktop->height() / level;
    int posXtop = 0;
    int posYtop = 0;
    while (posYtop > posY)
    {
        posYtop += Width;
    }
    while (posXtop > posX)
    {
        posXtop += Height;
    }
    drawGrid(scene, Width, Height, posXtop, posYtop);
    return (true);
}

void Layout::keyPressEvent ( QKeyEvent * keyEvent )
{
    //std::cout << "Layout::keyPressEvent = " << keyEvent->key() << std::endl;
    QList<QGraphicsItem *> items =  this->items();
    int sizeList = items.size();
    switch (keyEvent->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right :
        {
            QGraphicsItem * focusItem = this->focusItem();
            int index = items.indexOf(focusItem) + 1;
            QList<QGraphicsItem *>::iterator it = items.begin();
            if (index < sizeList)
                it += index;
            (*it)->setFocus();
        }
        break;
    case Qt::Key_Up :
    case Qt::Key_Down:
        {
            QGraphicsItem * focusItem = this->focusItem();
            int index = items.indexOf(focusItem) + 3;
            QList<QGraphicsItem *>::iterator it = items.begin();
            it += ((index < sizeList) ? index : (index - sizeList));
            (*it)->setFocus();
        }
        break;
    }
}
