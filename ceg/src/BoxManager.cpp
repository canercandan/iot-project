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

#include <QDesktopWidget>
#include <QApplication>
#include <QGraphicsRectItem>

#include "BoxManager.h"

#include "AbstractBox.h"
#include "Window.h"
#include "GraphicItemFactory.h"

BoxManager::BoxManager()
{
    //this->loadConf();
}

void    BoxManager::loadConf()
{
    std::list<AbstractBox*> list1;
    list1.push_back(new AbstractBox(DEFAULT, 0, std::list<AbstractBox*>(0), WindowGeometry(10, 10, 10, 10)));
    list1.push_back(new AbstractBox(DEFAULT, 0, std::list<AbstractBox*>(0), WindowGeometry(50, 50, 50, 50)));
}


void    BoxManager::getPattern(const Ceg::Window & aWindow, std::list<QGraphicsRectItem *> & graphicItems)
{
    std::map<std::string, std::list<AbstractBox *> >::iterator  itFind = this->_patterns.find(aWindow.getProgramName());
    std::list<AbstractBox *> childrenBox;
    if (itFind != this->_patterns.end())
    {
	childrenBox = itFind->second;
    }
    else
    {
	this->calcChildren(childrenBox, aWindow.getGeometry(), 0);
    }
    this->createGraphicItems(graphicItems, childrenBox);
}

void BoxManager::getChildren(std::list<QGraphicsRectItem *> & graphicItems, AbstractBox * box)
{
    std::list<AbstractBox *> childrenBox;
    if (box->getBoxType() == DEFAULT) // mode par default
    {
	this->calcChildren(childrenBox, box->getGeometry(), box->getLevel() + 1);
    }
    else // mode custom
    {
	childrenBox = box->getChilden();
    }
    this->createGraphicItems(graphicItems, childrenBox);
}

void BoxManager::getParent(std::list<QGraphicsRectItem *> & graphicItems, AbstractBox * box)
{
    std::list<AbstractBox *> childrenBox;
    if (box->getBoxType() == DEFAULT) // mode par default
    {
	this->calcParent(childrenBox, box);
    }
    else // mode custom
    {
	childrenBox = box->getParent()->getChilden();
    }
    this->createGraphicItems(graphicItems, childrenBox);
}

void BoxManager::createGraphicItems(std::list<QGraphicsRectItem *> & graphicItems, std::list<AbstractBox *> & boxs)
{
    for (std::list<AbstractBox *>::iterator it = boxs.begin(),
	 itEnd = boxs.end();
    it != itEnd; ++it)
    {
	graphicItems.push_back(GraphicItemFactory::create(*it));
    }
}

void BoxManager::calcChildren(std::list<AbstractBox *> & boxs, WindowGeometry const & geometry, unsigned short level)
{
    int nbGrid = 3;
    int tmpWidth = geometry._width / nbGrid;
    int tmpHeight = geometry._height / nbGrid;
    int rows = 0;
    int y = geometry._y;
    while (rows++ < nbGrid)
    {
	int cols = 0;
	qreal x = geometry._x;
	while (cols++ < nbGrid)
	{
	    boxs.push_back(new AbstractBox(DEFAULT, level, std::list<AbstractBox*>(0), WindowGeometry(x, y, tmpWidth, tmpHeight)));
	    x += tmpWidth;
	}
	y += tmpHeight;
    }
}


void BoxManager::calcParent(std::list<AbstractBox *> & boxs, AbstractBox * item)
{
    QDesktopWidget *desktop = QApplication::desktop();
    int level = item->getLevel();
    if (!level)
    {
	return ;
    }
    level--;
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
    int dynamicHeight = desktop->height() / 3;
    for (int i = 0; i < level; i++)
    {
	while ((posYtop + dynamicHeight) < item->getGeometry()._y + item->getGeometry()._height)
	{
	    posYtop += dynamicHeight;
	}
	dynamicHeight = dynamicHeight / 3;
    }

    int dynamicWidth = desktop->width() / 3;
    for (int i = 0; i < level; i++)
    {
	while ((posXtop + dynamicWidth) < item->getGeometry()._x + item->getGeometry()._width)
	{
	    posXtop += dynamicWidth;
	}
	dynamicWidth = dynamicWidth / 3;
    }
    this->calcChildren(boxs, WindowGeometry(posXtop, posYtop, Width, Height), item->getLevel() - 1);
}

