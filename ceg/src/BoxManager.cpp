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

#include <QDesktopWidget>
#include <QApplication>

#include "GraphicItemFactory.h"
#include "BoxManager.h"

BoxManager::BoxManager()
{
  //this->loadConf();
}

void    BoxManager::getPattern(std::string const & programName, const Ceg::Window & aWindow, std::list<QGraphicsRectItem *> & list)
{
	std::map<std::string, std::list<AbstractBox *> >::iterator  itFind = this->_patterns.find(programName);
	if (itFind != this->_patterns.end())
	{
		std::list<AbstractBox *>::iterator  it = itFind->second.begin();
		std::list<AbstractBox *>::iterator  itEnd = itFind->second.end();
		for (; it != itEnd; ++it)
		{
			list.push_back(GraphicItemFactory::create(*it));
		}
	}
	else
	{
		this->getDefaultPattern(list, aWindow);
	}
}

void BoxManager::drawDefaultChildren(std::list<QGraphicsRectItem *> & list, WindowGeometry const & geo, unsigned short level)
{
	int nbGrid = 3;
	int tmpWidth = geo._width / nbGrid;
	int tmpHeight = geo._height / nbGrid;
	int rows = 0;
	int y = geo._y;
	while (rows++ < nbGrid)
	{
		int cols = 0;
		qreal x = geo._x;
		while (cols++ < nbGrid)
		{
			list.push_back(GraphicItemFactory::create(new AbstractBox(DEFAULT, level, std::list<AbstractBox*>(0), WindowGeometry(x, y, tmpWidth, tmpHeight))));
			x += tmpWidth;
		}
		y += tmpHeight;
	}
}

void BoxManager::getDefaultPattern(std::list<QGraphicsRectItem *> & list, const Ceg::Window & aWindow)
{
	this->drawDefaultChildren(list, aWindow.getGeometry(), 0);
}

void BoxManager::getDefaultChildren(std::list<QGraphicsRectItem *> & list, AbstractBox * parent)
{
	this->drawDefaultChildren(list, parent->getGeometry(), parent->getLevel());
}

void BoxManager::getDefaultParent(std::list<QGraphicsRectItem *> & list, AbstractBox * item)
{
	QDesktopWidget *desktop = QApplication::desktop();
	int level = item->getLevel();
	if (!level)
	{
		return ;
	}
	//level--;
	//this->clearLayout();
	int Width = desktop->width();
	for (int i = 0; i < level; i++)
	{
		Width = Width / 3;
	}
	int Height = desktop->height();
	for (int i = 0; i < level; i++)
	{
		Height = Height / 3;
	}

	int posXtop = 0;
	int posYtop = 0;

	while ((posYtop + Height) < item->getGeometry()._y + item->getGeometry()._height)
	{
		posYtop += Height;
	}
	while ((posXtop + Width) < item->getGeometry()._x + item->getGeometry()._width)
	{
		posXtop += Width;
	}
	this->drawDefaultChildren(list, WindowGeometry(posXtop, posYtop, Width, Height), item->getLevel() - 1);
}

void    BoxManager::loadConf()
{
	std::list<AbstractBox*> list1;
	std::cout<< sizeof(list1) << std::endl;
	list1.push_back(new AbstractBox(DEFAULT, 0, std::list<AbstractBox*>(0), WindowGeometry(10, 10, 10, 10)));
	list1.push_back(new AbstractBox(DEFAULT, 0, std::list<AbstractBox*>(0), WindowGeometry(50, 50, 50, 50)));
}

