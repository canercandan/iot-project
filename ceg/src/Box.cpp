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
#include <QDomDocument>
/*********************************/
#include "Box.h"
/*********************************/
#include "ActionFactory.h"
#include "Utils.h"
#include "IAction.h"
#include "PopMenuAction.h"
#include "Logger.h"
/*********************************/


/************************************************* [ CTOR/DTOR ] *************************************************/

Box::Box(int level, QRect const & geometry):
	_type(DEFAULT_BOX), _geometry(geometry), _action(0), _graphicStyle(), _children()
{
    QDomDocument xmld;
    QDomElement actionElement = xmld.createElement("action");
    actionElement.setAttribute("id", QString(PopMenuAction::IDENTIFIER));
    actionElement.setAttribute("MenuId", "Event");
    this->_action = ActionFactory::create(actionElement);
    this->_topUnion._level = level;
}

Box::Box(const QDomElement& domElement, Box const * parent) :
	_type(CUSTOM_BOX), _geometry(), _action(0), _graphicStyle(), _children()
{
    this->_topUnion._parent = parent;
    this->initializeFromXml(domElement);
}

Box::~Box()
{
    std::for_each(this->_children.begin(), this->_children.end(), Ceg::DeleteObject());
    delete this->_action;
}

void Box::initializeFromXml(const QDomElement & boxElement)
{
    // revoir l'initialisation du type, les if pourront etre remove une fois les xsd en place
    if (boxElement.hasAttribute("type") == true)
	this->_type = static_cast<BoxType>(boxElement.attribute("type").toUInt());
    if (boxElement.hasAttribute("x") == true)
	this->_geometry.setX(boxElement.attribute("x").toInt());
    if (boxElement.hasAttribute("y") == true)
	this->_geometry.setY(boxElement.attribute("y").toInt());
    if (boxElement.hasAttribute("width") == true)
	this->_geometry.setWidth(boxElement.attribute("width").toInt());
    if (boxElement.hasAttribute("height") == true)
	this->_geometry.setHeight(boxElement.attribute("height").toInt());

    for (QDomNode domNode = boxElement.firstChild(); !domNode.isNull(); domNode = domNode.nextSibling())
    {
	QDomElement const & childElement = domNode.toElement();
	if (childElement.isNull() == false)
	{
	    QString const & tagName = childElement.tagName();
	    if (tagName == "action")
	    {
		this->_action = ActionFactory::create(childElement);
	    }
	    else if (tagName == "style")
	    {
		this->_graphicStyle = BoxStyle(childElement);
	    }
	    else if (tagName == "children")
	    {
		this->createChildren(childElement);
	    }
	}
    }
}

void Box::createChildren(QDomElement const & childrenElement)
{
    for (QDomNode boxNode = childrenElement.firstChild(); !boxNode.isNull(); boxNode = boxNode.nextSibling())
    {
	QDomElement const & boxElement = boxNode.toElement();
	if (boxElement.isNull() == false && boxElement.tagName() == "box")
	{
	    this->_children.push_back(new Box(boxElement, this));
	}
    }
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

QList<Box const *> const &    Box::getChilden() const
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

BoxStyle const &	Box::getGraphicStyle() const
{
    return (this->_graphicStyle);
}
