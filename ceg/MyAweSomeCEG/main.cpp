#include <iostream>

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "MyAweSomeBox.h"
#include "Layout.h"


void    drawGrid(QGraphicsScene & scene, int width, int height, int posX = 0, int posY = 0)
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

void    drawChild(QGraphicsScene & scene, QGraphicsRectItem & item)
{
    drawGrid(scene, item.rect().width(), item.rect().height(), item.rect().x(), item.rect().y());
}

bool    drawParent(QGraphicsScene & scene, int posX, int posY, int width)
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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDesktopWidget *desktop = QApplication::desktop();
    int WinWidth = desktop->width();
    int WinHeight = desktop->height() - 100;

    Layout scene(0, 0, WinWidth, WinHeight);
    drawGrid(scene, WinWidth, WinHeight);
    QList<QGraphicsItem *> items =  scene.items ();
    items.first()->setFocus();

    QGraphicsView view(&scene);
    view.setWindowOpacity(0.5);
    view.show();
    return (a.exec());
}
