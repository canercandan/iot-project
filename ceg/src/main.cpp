#include <QtGui/QApplication>

#include "LayerManager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LayerManager    layerManager;
    layerManager.init();
    layerManager.start();
    return (a.exec());
}
