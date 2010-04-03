#ifndef ABSTRACTBOX_H
#define ABSTRACTBOX_H

#include <list>

#include "WindowGeometry.h"

enum BoxType {DEFAULT, CUSTOM, MENU};

class AbstractBox
{
public:
    AbstractBox();

    WindowGeometry const & getGeometry() const;

private:
    BoxType _type;
    AbstractBox * _parent;
    std::list<AbstractBox *>    _children;
    WindowGeometry  _geometry;
};

#endif // ABSTRACTBOX_H
