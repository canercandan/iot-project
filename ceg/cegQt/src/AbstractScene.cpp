#include <QKeyEvent>

#include "AbstractScene.h"

AbstractScene::AbstractScene(qreal x, qreal y, qreal width, qreal height, QObject * parent) :
        QGraphicsScene(x, y, width, height, parent)
{
}

void AbstractScene::initScene(std::list<QGraphicsRectItem *> &newScene)
{
    this->clearScene();
    std::list<QGraphicsRectItem *>::const_iterator  it = newScene.begin();
    std::list<QGraphicsRectItem *>::const_iterator  itEnd = newScene.end();

    for (; it != itEnd; ++it)
    {
        this->addItem(*it);
    }
    newScene.front()->setFocus();
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

void AbstractScene::keyPressEvent(QKeyEvent * keyEvent)
{
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
    /*case Qt::Key_Return :
        this->drawChild(this->focusItem());
        break;
    case Qt::Key_Backspace :
        this->drawParent(this->focusItem());
        break;*/
    }
}
