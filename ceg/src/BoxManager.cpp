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
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>

#include "BoxManager.h"

#include "Box.h"
#include "Window.h"
#include "GraphicItemFactory.h"

/************************************************* [ CTOR/DTOR ] *************************************************/

BoxManager::BoxManager()
{
    //this->loadConf();
}

BoxManager::~BoxManager()
{
    for (std::map< std::string, std::list< Box * > >::const_iterator it = this->_patterns.begin(), end = this->_patterns.end();
    it != end; ++it)
    {
	std::list< Box* > const & ablist = it->second;

	for (std::list<Box*>::const_iterator it = ablist.begin(), end = ablist.end();
	it != end; ++it)
	{
	    delete *it;
	}
    }
}

/************************************************* [ GETTERS ] *************************************************/

void BoxManager::getChildren(std::list<QGraphicsRectItem *> & graphicItems, Box const * box) const
{
    std::list<Box *> childrenBox;
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

void BoxManager::getParent(std::list<QGraphicsRectItem *> & graphicItems, Box const * box) const
{
    std::list<Box *> childrenBox;
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

//! This method uses window name to get all AbstractBox[es] (got initially from XML).
//! The list of AbstractBox is used to generate Item objects which is an area of the view.
void    BoxManager::getPattern(Ceg::Window const & aWindow, std::list<QGraphicsRectItem *> & graphicItems) const
{
    std::map<std::string, std::list<Box *> >::const_iterator  itFind = this->_patterns.find(aWindow.getProgramName());
    std::list<Box *> childrenBox;
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

//! This method is used in the case we are using a grid view,
//! indeed it is going to calculate position and size of each
//! grid areas in function of _nbGrid static value.
void BoxManager::calcChildren(std::list<Box *> & boxs, QRect const & geometry, unsigned short level) const
{
    int tmpWidth = geometry.width() / NBGRID;
    int tmpHeight = geometry.height() / NBGRID;
    int rows = 0;
    int y = geometry.y();
    while (rows++ < NBGRID)
    {
	int cols = 0;
	qreal x = geometry.x();
	while (cols++ < NBGRID)
	{
	    boxs.push_back(new Box(DEFAULT, level, std::list<Box*>(0), QRect(x, y, tmpWidth, tmpHeight)));
	    x += tmpWidth;
	}
	y += tmpHeight;
    }
}

void BoxManager::calcParent(std::list<Box *> & boxs, Box const * item) const
{
    QDesktopWidget *desktop = QApplication::desktop();
    int level = item->getLevel();
    if (!level)
    {
	return ;
    }
    level--;
    int width = desktop->width();
    for (int i = 0; i < level; ++i)
    {
	width /= NBGRID;
    }
    int height = desktop->height();
    for (int i = 0; i < level; ++i)
    {
	height /= NBGRID;
    }

    int posXtop = 0;
    int posYtop = 0;
    int dynamicHeight = desktop->height() / NBGRID;
    int maxHeight = item->getGeometry().y() + item->getGeometry().height();
    for (int i = 0; i < level; ++i)
    {
	while ((posYtop + dynamicHeight) < maxHeight)
	{
	    posYtop += dynamicHeight;
	}
	dynamicHeight /= NBGRID;
    }

    int dynamicWidth = desktop->width() / NBGRID;
    int maxWidth = item->getGeometry().x() + item->getGeometry().width();
    for (int i = 0; i < level; ++i)
    {
	while ((posXtop + dynamicWidth) < maxWidth)
	{
	    posXtop += dynamicWidth;
	}
	dynamicWidth /= NBGRID;
    }
    this->calcChildren(boxs, QRect(posXtop, posYtop, width, height), item->getLevel() - 1);
}

void BoxManager::createGraphicItems(std::list<QGraphicsRectItem *> & graphicItems, std::list<Box *> const & boxs) const
{
    for (std::list<Box *>::const_iterator it = boxs.begin(), itEnd = boxs.end(); it != itEnd; ++it)
    {
	graphicItems.push_back(GraphicItemFactory::create(*it));
    }
}

void    BoxManager::loadConf(const QString& name)
{
    QFile	file(QString("config/" + name + ".xml"));
    QDomDocument doc(name);

    if (!file.open(QIODevice::ReadOnly) || !doc.setContent( &file ))
    {
	QMessageBox::warning(0, "Loading", "Failed to load file.");
	return;
    }

    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != "boxes")
    {
	QMessageBox::warning(0, "Loading", "Invalid file.");
	return;
    }

    std::list<Box*> & ablist = this->_patterns[name.toStdString()];

    ablist.clear();

    for (QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
    {
	QDomElement e = n.toElement();
	if (e.isNull())
	    continue;
	if (e.tagName() != "box")
	    continue;

	Box* b = new Box(e);
	ablist.push_back(b);
    }
}
