#ifndef LAYER_H
#define LAYER_H

#include "AbstractScene.h"
#include "Window.h"

class Layer : public AbstractScene
{
public:
    Layer(Ceg::Window const &);

    virtual WindowGeometry  getGeometry() const;

private:
    Ceg::Window _host;
};

#endif // LAYER_H