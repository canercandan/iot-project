#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

#include <list>

#include <QGraphicsScene>
#include <QGraphicsRectItem>

class AbstractScene : public QGraphicsScene
{
public:
    AbstractScene();

    void drawScene(std::list<QGraphicsRectItem *> & newScene);

private:
    void clearScene();
};

#endif // ABSTRACTSCENE_H
