#include "includes\LayerManager.h"

LayerManager::LayerManager()
{
    /*    QDesktopWidget *desktop = QApplication::desktop();
        Layout scene(0, 0, desktop->width(), desktop->height() - 100);

        QGraphicsView view(&scene);
        view.setWindowOpacity(0.5);
        view.show();*/
}

void LayerManager::start()
{
    this->_view.show();
}
