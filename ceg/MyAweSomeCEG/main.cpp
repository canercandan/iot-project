#include <iostream>

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "MyAweSomeBox.h"


bool drawParent(int posX, int posY, int width)
{
  int level = QApplication::desktop()->width() / width;
  if (!level)
    {
      return (false);
    }
  return (true);
}

void    drawGrid(QGraphicsScene & scene, int width, int height)
{
    int posX = 0;
    int posY = 0;
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
            posY += tmpWidth;
        }
        posY = 0;
        posX += tmpHeight;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDesktopWidget *desktop = QApplication::desktop();
    int WinWidth = desktop->width() - 100;
    int WinHeight = desktop->height() - 100;

    QGraphicsScene scene(0, 0, WinWidth, WinHeight);
    drawGrid(scene, WinWidth, WinHeight);

    QGraphicsView view(&scene);
    view.setWindowOpacity(0.1);
    view.show();
    /*scene->setItemIndexMethod(QGraphicsScene::NoIndex);
 void GraphWidget::keyPressEvent(QKeyEvent *event)
 QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
update();*/
    return a.exec();
}
