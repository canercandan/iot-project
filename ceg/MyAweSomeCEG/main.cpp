#include <iostream>
#include <QtGui/QApplication>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "MyAweSomeBox.h"



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
