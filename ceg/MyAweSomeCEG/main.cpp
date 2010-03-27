#include <iostream>
#include <QtGui/QApplication>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui/QDesktopWidget>

#include "MyAweSomeBox.h"


#include <iostream>
void    drawGrid(int width, int height)
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
	  std::cout << "\n\n" << "Block (" << rows << ", " << cols << "):" << std::endl;
	  std::cout << "PosX: " << posX << "\nposY: " << posY << "\nGWidth: " << tmpWidth << "\nHeight: " << tmpHeight << std::endl;
	  posX += tmpWidth;
        }
      posX = 0;
      posY += tmpHeight;
    }
}

void     topLevelGrid()
{
  QDesktopWidget *desktop = QApplication::desktop();
  std::cout << desktop->width() << std::endl;
  std::cout << desktop->height() << std::endl;
  int WinWidth = desktop->width();
  int WinHeight = desktop->height();
  drawGrid(WinWidth, WinHeight);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     QGraphicsScene scene(50,50,650,650);
    MyAweSomeBox *rect = new MyAweSomeBox(20, 10, 900, 200);
    scene.addItem(rect);
    rect = new MyAweSomeBox(350, 400, 350, 900);
    scene.addItem(rect);

    scene.setFocus();
    scene.setFocusItem(rect);


  QGraphicsView view(&scene);
  view.setWindowOpacity(0.5);
 view.show();


 /*scene->setItemIndexMethod(QGraphicsScene::NoIndex);
 void GraphWidget::keyPressEvent(QKeyEvent *event)
 QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
update();*/


    return a.exec();
}
