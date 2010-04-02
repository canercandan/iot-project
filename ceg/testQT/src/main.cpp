#include <iostream>

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>

#include "MyAweSomeBox.h"
#include "Layout.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDesktopWidget *desktop = QApplication::desktop();
    Layout scene(0, 0, desktop->width(), desktop->height() - 100);

    QGraphicsView view(&scene);
    view.setWindowOpacity(0.5);
    view.show();
    return (a.exec());
}
