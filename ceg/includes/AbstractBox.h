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

class WindowGeometry;

enum BoxType {DEFAULT, CUSTOM, MENU};

class AbstractBox
{
public:
    AbstractBox(WindowGeometry geometry, BoxType boxtype);
    AbstractBox(BoxType boxtype, AbstractBox* _parent,
		std::list<AbstractBox*> children, WindowGeometry geometry);
    AbstractBox(BoxType boxtype, int level,
		std::list<AbstractBox*> children, WindowGeometry geometry);

    ~AbstractBox();
    WindowGeometry const &	getGeometry() const;
    unsigned short		getLevel() const;
    std::list<AbstractBox *> const &	getChilden() const;
    AbstractBox *		getParent() const;
    BoxType			getBoxType() const;

private:
    BoxType						_type;
    union uniontype
    {
	AbstractBox*			_parent;
	int						_level;
    }							_topUnion;
    std::list<AbstractBox *>    _children;
    WindowGeometry				_geometry;
};

#endif // ABSTRACTBOX_H
