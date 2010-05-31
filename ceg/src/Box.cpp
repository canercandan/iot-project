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

/*********************************/
#include <algorithm>
/*********************************/
#include <QDomElement>
/*********************************/
#include "Box.h"
/*********************************/
#include "Utils.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

Box::Box(BoxType boxtype, Box const * parent, std::list<Box const *> const & children, QRect const & geometry):
	_type(boxtype), _geometry(geometry), _action(0), _children(children)
{
    this->_topUnion._parent = parent;
}

Box::Box(BoxType boxtype, int level, std::list<Box const *> const & children, QRect const & geometry):
	_type(boxtype), _geometry(geometry), _action(0), _children(children)
{
    this->_topUnion._level = level;
}

Box::Box(const QDomElement& domElement, Box const * parent) :
	_action(0), _children()
{
    this->_topUnion._parent = parent;
    this->initializeFromXml(domElement);
}

Box::~Box()
{
    std::for_each(this->_children.begin(), this->_children.end(), Ceg::DeleteObject());
}

void Box::initializeFromXml(const QDomElement & domElement)
{
    if (domElement.hasAttribute("type") == true)
	this->_type = static_cast<BoxType>(domElement.attribute("type").toUInt());
    if (domElement.hasAttribute("x") == true)
	this->_geometry.setX(domElement.attribute("x").toUInt());
    if (domElement.hasAttribute("y") == true)
	this->_geometry.setY(domElement.attribute("y").toUInt());
    if (domElement.hasAttribute("width") == true)
	this->_geometry.setWidth(domElement.attribute("width").toUInt());
    if (domElement.hasAttribute("height") == true)
	this->_geometry.setHeight(domElement.attribute("height").toUInt());

    /*    for (QDomNode domNode = domElement.firstChild(); !domNode.isNull(); domNode = domNode.nextSibling())
    {
	QDomElement e2 = domNode.toElement();
	if (e2.isNull())
	    continue;
	if (e2.tagName() != "param")
	    continue;
    }*/
}

/************************************************* [ GETTERS ] *************************************************/

IAction *   Box::getAction() const
{
    return (this->_action);
}

BoxType	Box::getBoxType() const
{
    return (this->_type);
}

std::list<Box const *> const &    Box::getChilden() const
{
    return (this->_children);
}

QRect const &	Box::getGeometry() const
{
    return (this->_geometry);
}

unsigned short	Box::getLevel() const
{
    return (this->_topUnion._level);
}

Box const *	Box::getParent() const
{
    return (this->_topUnion._parent);
}
