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

#include "BoxManager.h"

#include "AbstractBox.h"
#include "Window.h"
#include "GraphicItemFactory.h"

/************************************************* [ VARIABLES ] *************************************************/

const int	BoxManager::_nbGrid = 1000;

/************************************************* [ CTOR/DTOR ] *************************************************/

BoxManager::BoxManager()
{
  //this->loadConf();
}

BoxManager::~BoxManager()
{
  for (std::map< std::string, std::list< AbstractBox * > >::iterator
	 it = this->_patterns.begin(),
	 end = this->_patterns.end();
       it != end; ++it)
    {
      std::list< AbstractBox* > & ablist = it->second;

      for (std::list<AbstractBox*>::iterator
	     it = ablist.begin(),
	     end = ablist.end();
	   it != end; ++it)
	{
	  delete *it;
	}
    }
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

//! This method uses window name to get all AbstractBox[es] (got initially from XML).
//! The list of AbstractBox is used to generate Item objects which is an area of the view.
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

//! This method is used in the case we are using a grid view,
//! indeed it is going to calculate position and size of each
//! grid areas in function of _nbGrid static value.
void BoxManager::calcChildren(std::list<AbstractBox *> & boxs, QRect const & geometry, unsigned short level) const
{
    int tmpWidth = geometry.width() / _nbGrid;
    int tmpHeight = geometry.height() / _nbGrid;
    int rows = 0;
    int y = geometry.y();
    while (rows++ < _nbGrid)
    {
	int cols = 0;
	qreal x = geometry.x();
	while (cols++ < _nbGrid)
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
      Width /= _nbGrid;
    }
  int Height = desktop->height();
  for (int i = 0; i < level; ++i)
    {
      Height /= _nbGrid;
    }

  int posXtop = 0, posYtop = 0, dynamicHeight = desktop->height() / _nbGrid, maxHeight = item->getGeometry().y() + item->getGeometry().height();
  for (int i = 0; i < level; ++i)
    {
      while ((posYtop + dynamicHeight) < maxHeight)
	{
	  posYtop += dynamicHeight;
	}
      dynamicHeight /= _nbGrid;
    }
  int dynamicWidth = desktop->width() / _nbGrid, maxWidth = item->getGeometry().x() + item->getGeometry().width();
  for (int i = 0; i < level; ++i)
    {
      while ((posXtop + dynamicWidth) < maxWidth)
	{
	  posXtop += dynamicWidth;
	}
      dynamicWidth /= _nbGrid;
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

void    BoxManager::loadConf(const QString& name)
{
  //     std::list<AbstractBox*> list1;
  //     list1.push_back(new AbstractBox(DEFAULT, 0, std::list<AbstractBox*>(0), QRect(10, 10, 10, 10)));
  //     list1.push_back(new AbstractBox(DEFAULT, 0, std::list<AbstractBox*>(0), QRect(50, 50, 50, 50)));

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

  std::list<AbstractBox*> & ablist = this->_patterns[name.toStdString()];

  ablist.clear();

  for (QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
    {
      QDomElement e = n.toElement();
      if (e.isNull())
	continue;
      if (e.tagName() != "box")
	continue;

      AbstractBox* b = new AbstractBox(e);
      ablist.push_back(b);
    }
}

void    BoxManager::saveConf(const QString& name)
{
  QDomDocument doc(name);
  QDomElement root = doc.createElement("boxes");
  doc.appendChild(root);

  std::list<AbstractBox*> & ablist = this->_patterns[name.toStdString()];

  for (std::list<AbstractBox*>::iterator
	 it = ablist.begin(),
	 end = ablist.end();
       it != end; ++it)
    {
      root.appendChild( (*it)->createXMLNode(doc) );
    }

  QFile file(QString("config/" + name + ".xml"));
  if (!file.open(QIODevice::WriteOnly))
    {
      QMessageBox::warning(0, "Saving", "Failed to save file.");
      return;
    }

  QTextStream ts(&file);
  ts << doc.toString();

  file.close();
}
