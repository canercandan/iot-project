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

#include "AbstractBox.h"
#include "BoxParameter.h"

/************************************************* [ CTOR/DTOR ] *************************************************/

AbstractBox::AbstractBox(BoxType boxtype, AbstractBox * parent, std::list<AbstractBox*> const & children, QRect const & geometry):
  _visible(false), _opacity(0), _type(boxtype), _geometry(geometry),
  _action(0), _children(children)
{
    this->_topUnion._parent = parent;
}

AbstractBox::AbstractBox(BoxType boxtype, int level, std::list<AbstractBox*> const & children, QRect const & geometry):
  _visible(false), _opacity(0), _type(boxtype), _geometry(geometry),
  _actionid(""), _action(0), _children(children)
{
    this->_topUnion._level = level;
}

AbstractBox::AbstractBox(const QDomElement& e)
{
  if (e.hasAttribute("visible"))
    this->_visible = e.attribute("visible").toUInt();
  if (e.hasAttribute("opacity"))
    this->_opacity = e.attribute("opacity").toUInt();
  if (e.hasAttribute("type"))
    this->_type = static_cast<BoxType>(e.attribute("type").toUInt());

  if (e.hasAttribute("x"))
    this->_geometry.setX(e.attribute("x").toUInt());
  if (e.hasAttribute("y"))
    this->_geometry.setY(e.attribute("y").toUInt());
  if (e.hasAttribute("width"))
    this->_geometry.setWidth(e.attribute("width").toUInt());
  if (e.hasAttribute("height"))
    this->_geometry.setHeight(e.attribute("height").toUInt());

  if (e.hasAttribute("actionid"))
    this->_actionid = e.attribute("actionid");

  for (QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling())
    {
      QDomElement e2 = n.toElement();
      if (e2.isNull())
	continue;
      if (e2.tagName() != "param")
	continue;

      IXmlNode* p = new BoxParameter(e2);
      this->_params.push_back(p);
    }
}

AbstractBox::~AbstractBox()
{
  for (std::list<AbstractBox*>::iterator it = this->_children.begin(), ite = this->_children.end(); it != ite;)
    {
      AbstractBox const * const tempBox = *it;
      it = this->_children.erase(it); // ??? quel interet de erase un element d'une liste situé dans la stack ??? La liste va de toute façon etre viré à la destruction de la classe
      delete (tempBox);
    }

  for (std::list<IXmlNode*>::iterator
	 it = this->_params.begin(),
	 end = this->_params.end();
       it != end; ++it)
    {
      delete *it;
    }
}

QDomElement AbstractBox::createXMLNode(QDomDocument& d)
{
  QDomElement cn = d.createElement("box");

  cn.setAttribute("visible", this->_visible);
  cn.setAttribute("opacity", this->_opacity);
  cn.setAttribute("type", this->_type);

  cn.setAttribute("x", this->_geometry.x());
  cn.setAttribute("y", this->_geometry.y());
  cn.setAttribute("width", this->_geometry.width());
  cn.setAttribute("height", this->_geometry.height());

  cn.setAttribute("actionid", this->_actionid);

  //   cn.setAttribute("image", _image);
  //   cn.setAttribute("text", _text);

  for (std::list<IXmlNode*>::iterator
	 it = this->_params.begin(),
	 end = this->_params.end();
       it != end; ++it)
    {
      cn.appendChild( (*it)->createXMLNode(d) );
    }

  return cn;
}

/************************************************* [ GETTERS ] *************************************************/

IAction *   AbstractBox::getAction() const
{
    return (this->_action);
}

BoxType	AbstractBox::getBoxType() const
{
    return (this->_type);
}

std::list<AbstractBox *> const &    AbstractBox::getChilden() const
{
    return (this->_children);
}

QRect const &	AbstractBox::getGeometry() const
{
    return (this->_geometry);
}

unsigned short	AbstractBox::getLevel() const
{
    return (this->_topUnion._level);
}

AbstractBox *	AbstractBox::getParent() const
{
    return (this->_topUnion._parent);
}
