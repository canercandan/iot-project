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
	Layout scene(0, 0, desktop->width(), desktop->height());

	QGraphicsView view(&scene);
	view.setGeometry(0, 0, desktop->width(), desktop->height());
	view.setWindowOpacity(0.5);
	view.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view.show();

	return (a.exec());
}
