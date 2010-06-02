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

#ifndef BOX_H_
#define BOX_H_

#include <list>
#include <map>

#include <QRect>

#include "IDomFactory.h"
#include "BoxStyle.h"

class IAction;
class BoxParameter;

enum BoxType {DEFAULT_BOX = 0, CUSTOM_BOX, MENU_BOX};

class Box : public IDomFactory
{
public:
    Box(QRect geometry, BoxType boxtype);
    Box(BoxType boxtype, Box const * parent, std::list<Box const *> const & children, QRect const & geometry);
    Box(BoxType boxtype, int level, std::list<Box const *> const & children, QRect const & geometry);
    Box(QDomElement const & domElement, Box const * parent);
    ~Box();

    IAction  *			    getAction() const;
    BoxType			    getBoxType() const;
    std::list<Box const *> const &  getChilden() const;
    QRect const &		    getGeometry() const;
    unsigned short		    getLevel() const;
    Box const *			    getParent() const;

private :
	virtual void initializeFromXml(QDomElement const & boxElement);
void	createChildren(QDomElement const & childrenElement);

private:
BoxType		    _type;
union
{
    Box const *	    _parent;
    int			    _level;
}			    _topUnion;
QRect			    _geometry;
IAction  *		    _action;
BoxStyle		_graphicSytle;
std::list<Box const *>   _children;
};

#endif // BOX_H_
