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

#ifndef ABSTRACTBOX_H
#define ABSTRACTBOX_H

#include <list>

#include <QRect>
#include <QtXml>

#include "IXmlNode.h"

class IAction;

enum BoxType {DEFAULT, CUSTOM, MENU};

class AbstractBox : public IXmlNode
{
public:
  AbstractBox(QRect geometry, BoxType boxtype);
  AbstractBox(BoxType boxtype, AbstractBox * parent, std::list<AbstractBox*> const & children, QRect const & geometry);
  AbstractBox(BoxType boxtype, int level, std::list<AbstractBox*> const & children, QRect const & geometry);
  //AbstractBox(const QDomElement& e);
  ~AbstractBox();

  virtual QDomElement createXMLNode(QDomDocument& d);

  IAction*			    getAction() const;
  BoxType			    getBoxType() const;
  std::list<AbstractBox *> const &  getChilden() const;
  QRect const &			    getGeometry() const;
  unsigned short		    getLevel() const;
  AbstractBox*			    getParent() const;

private:
  BoxType		    _type;
  union
  {
    AbstractBox*	    _parent;
    int			    _level;
  }			    _topUnion;
  std::list<AbstractBox *>  _children;
  QRect			    _geometry;
  IAction*		    _action;
};

#endif // ABSTRACTBOX_H
