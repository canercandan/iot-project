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

#ifndef BOXMANAGER_H
#define BOXMANAGER_H

#include <map>
#include <list>
#include <string>

#include <QGraphicsRectItem>

#include "AbstractBox.h"
#include "Window.h"

class BoxManager
{
public:
	BoxManager();

	void getPattern(std::string const &, Ceg::Window const &, std::list<QGraphicsRectItem *> & list);
	/*
	** load les configurations xml dans _patterns
	*/
	void	loadConf();

private:
	void    getDefaultPattern(std::list<QGraphicsRectItem *> &, const Ceg::Window &);
	void	getDefaultChildren(std::list<QGraphicsRectItem *> &, AbstractBox *);
	void	drawDefaultChildren(std::list<QGraphicsRectItem *> &, WindowGeometry const &, unsigned short);
	void	getDefaultParent();
	void	getDefaultParent(std::list<QGraphicsRectItem *> &, AbstractBox *);

private:
	std::map<std::string, std::list<AbstractBox *> > _patterns;
};

#endif // BOXMANAGER_H
