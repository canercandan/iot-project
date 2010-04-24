#ifndef ABSTRACTBOX_H
#define ABSTRACTBOX_H

#include <list>

#include "WindowGeometry.h"

enum BoxType {DEFAULT, CUSTOM, MENU};

class AbstractBox
{
public:
    AbstractBox(WindowGeometry geometry, BoxType boxtype);
    AbstractBox(BoxType boxtype, AbstractBox* _parent,
                std::list<AbstractBox*> children, WindowGeometry geometry);

    ~AbstractBox();
    WindowGeometry const & getGeometry() const;

private:
    BoxType			_type;
    AbstractBox*		_parent;
    std::list<AbstractBox *>    _children;
    WindowGeometry		_geometry;
};

#endif // ABSTRACTBOX_H
