#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

#include <list>

#include <QGraphicsScene>
#include <QGraphicsRectItem>

class AbstractScene : public QGraphicsScene
{
public:
    AbstractScene(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0);

    virtual void initScene(std::list<QGraphicsRectItem *> & newScene);
    void    keyPressEvent(QKeyEvent * keyEvent);

private:
    void clearScene();
};

#endif // ABSTRACTSCENE_H
