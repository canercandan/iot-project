#include <iostream>

#include "includes/AbstractBox.h"

AbstractBox::AbstractBox(BoxType boxtype, AbstractBox* parent,
			 std::list<AbstractBox*> children, WindowGeometry geometry):
_type(boxtype), _parent(parent), _children(children), _geometry(geometry)

{
}

AbstractBox::~AbstractBox()
{
    std::cout<< "~AbstractBox" <<std::endl;
    std::list<AbstractBox*>::iterator it, ite, save;
    for(it = this->_children.begin(), ite = this->_children.end(); it != ite; )
    {
      save = it;
      ++it;
      this->_children.erase(save);
    }
}

WindowGeometry const & AbstractBox::getGeometry() const
{
    return (this->_geometry);
}
