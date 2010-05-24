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

/************************************************* [ CTOR/DTOR ] *************************************************/

BoxManager::BoxManager()
{
    //this->loadConf();
}

/************************************************* [ GETTERS ] *************************************************/

void BoxManager::getChildren(std::list<QGraphicsRectItem *> & graphicItems, AbstractBox const * box) const
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

void BoxManager::getParent(std::list<QGraphicsRectItem *> & graphicItems, AbstractBox const * box) const
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

void    BoxManager::getPattern(Ceg::Window const & aWindow, std::list<QGraphicsRectItem *> & graphicItems) const
{
    std::map<std::string, std::list<AbstractBox *> >::const_iterator  itFind = this->_patterns.find(aWindow.getProgramName());
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

/************************************************* [ OTHERS ] *************************************************/

void BoxManager::calcChildren(std::list<AbstractBox *> & boxs, QRect const & geometry, unsigned short level) const
{
    int nbGrid = 3;
    int tmpWidth = geometry.width() / nbGrid;
    int tmpHeight = geometry.height() / nbGrid;
    int rows = 0;
    int y = geometry.y();
    while (rows++ < nbGrid)
    {
	int cols = 0;
	qreal x = geometry.x();
	while (cols++ < nbGrid)
	{
	    boxs.push_back(new AbstractBox(DEFAULT, level, std::list<AbstractBox*>(0), QRect(x, y, tmpWidth, tmpHeight)));
	    x += tmpWidth;
	}
	y += tmpHeight;
    }
}

void BoxManager::calcParent(std::list<AbstractBox *> & boxs, AbstractBox const * item) const
{
    QDesktopWidget *desktop = QApplication::desktop();
    int level = item->getLevel();
    if (!level)
    {
	return ;
    }
    level--;
    int Width = desktop->width();
    for (int i = 0; i < level; ++i)
    {
	Width /= 3;
    }
    int Height = desktop->height();
    for (int i = 0; i < level; ++i)
    {
	Height /= 3;
    }

    int posXtop = 0, posYtop = 0, dynamicHeight = desktop->height() / 3, maxHeight = item->getGeometry().y() + item->getGeometry().height();
    for (int i = 0; i < level; ++i)
    {
	while ((posYtop + dynamicHeight) < maxHeight)
	{
	    posYtop += dynamicHeight;
	}
	dynamicHeight /= 3;
    }
    int dynamicWidth = desktop->width() / 3, maxWidth = item->getGeometry().x() + item->getGeometry().width();
    for (int i = 0; i < level; ++i)
    {
	while ((posXtop + dynamicWidth) < maxWidth)
	{
	    posXtop += dynamicWidth;
	}
	dynamicWidth /= 3;
    }
    this->calcChildren(boxs, QRect(posXtop, posYtop, Width, Height), item->getLevel() - 1);
}

void BoxManager::createGraphicItems(std::list<QGraphicsRectItem *> & graphicItems, std::list<AbstractBox *> const & boxs) const
{
    for (std::list<AbstractBox *>::const_iterator it = boxs.begin(), itEnd = boxs.end(); it != itEnd; ++it)
    {
	graphicItems.push_back(GraphicItemFactory::create(*it));
    }
}

void    BoxManager::loadConf() const
{
    std::list<AbstractBox*> list1;
    list1.push_back(new AbstractBox(DEFAULT, 0, std::list<AbstractBox*>(0), QRect(10, 10, 10, 10)));
    list1.push_back(new AbstractBox(DEFAULT, 0, std::list<AbstractBox*>(0), QRect(50, 50, 50, 50)));
}
