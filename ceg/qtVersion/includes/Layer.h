#ifndef LAYER_H
#define LAYER_H

#include "AbstractScene.h"
#include "Window.h"

class Layer : public AbstractScene
{
public:
    Layer();

private:
    Ceg::Window _host;
};

#endif // LAYER_H
