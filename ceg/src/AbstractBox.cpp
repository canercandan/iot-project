// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyright (C) 2010 CEG development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Authors: CEG <ceg@ionlythink.com>, http://www.ionlythink.com
 */

#include <iostream>

#include "AbstractBox.h"

#include <QRect>

AbstractBox::AbstractBox(BoxType boxtype, AbstractBox* parent,
			 std::list<AbstractBox*> children, QRect geometry):
_type(boxtype), _children(children), _geometry(geometry), _action(0)
{
    this->_topUnion._parent = parent;
}

AbstractBox::AbstractBox(BoxType boxtype, int level,
			 std::list<AbstractBox*> children, QRect geometry):
_type(boxtype), _children(children), _geometry(geometry), _action(0)
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

QRect const & AbstractBox::getGeometry() const
{
    return (this->_geometry);
}


unsigned short	AbstractBox::getLevel() const
{
    return (this->_topUnion._level);
}

std::list<AbstractBox *> const &	AbstractBox::getChilden() const
{
    return (this->_children);
}

AbstractBox * AbstractBox::getParent() const
{
    return (this->_topUnion._parent);
}

BoxType			AbstractBox::getBoxType() const
{
    return (this->_type);
}

IAction *   AbstractBox::getAction()
{
    return (this->_action);
}
