#include <iostream>

#include "AbstractBox.h"

AbstractBox::AbstractBox(BoxType boxtype, AbstractBox* parent,
			 std::list<AbstractBox*> children, WindowGeometry geometry):
_type(boxtype), _children(children), _geometry(geometry)
{
	this->_topUnion._parent = parent;
}

AbstractBox::AbstractBox(BoxType boxtype, int level,
			 std::list<AbstractBox*> children, WindowGeometry geometry):
_type(boxtype), _children(children), _geometry(geometry)
{
	this->_topUnion._level = level;
}

AbstractBox::~AbstractBox()
{
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


unsigned short	AbstractBox::getLevel() const
{
	return (this->_topUnion._level);
}
