#include "AbstractScene.h"

AbstractScene::AbstractScene() : QGraphicsScene()
{
}

void AbstractScene::drawScene(std::list<QGraphicsRectItem *> &newScene)
{
    this->clearScene();
    std::list<QGraphicsRectItem *>::const_iterator  it = newScene.begin();
    std::list<QGraphicsRectItem *>::const_iterator  itEnd = newScene.end();

    for (; it != itEnd; ++it)
    {
        this->addItem(*it);
    }
}

void AbstractScene::clearScene()
{
    QList<QGraphicsItem *> items = this->items();
    QList<QGraphicsItem *>::iterator it = items.begin();
    for (; it != items.end();)
    {
        QList<QGraphicsItem *>::iterator itTemp = it;
        ++itTemp;
        QGraphicsItem * tmpItem = *it;
        this->removeItem(tmpItem);
        delete tmpItem;
        it = itTemp;
    }
}