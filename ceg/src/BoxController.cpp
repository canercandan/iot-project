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

/*********************************/
#include <iostream>
#include <algorithm>
/*********************************/
#include <QDesktopWidget>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QDir>
/*********************************/
#include "BoxController.h"
/*********************************/
#include "Box.h"
#include "Window.h"
#include "GraphicItemFactory.h"
#include "Utils.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

BoxController::BoxController() :
	_patterns(), _menus()
#ifndef Q_WS_WIN
	, _logger(log4cxx::Logger::getLogger("ceg.boxfactory"))
#endif
{
#ifndef Q_WS_WIN
    LOG4CXX_INFO(this->_logger, "Chargement des fichiers xml pour les programmes");
#endif

    this->initializeFromConfig("config");

#ifndef Q_WS_WIN
    LOG4CXX_INFO(this->_logger, "Chargement des fichiers xml pour les menus");
#endif

    this->initializeFromXml("../resources/xml/menus/EventMenu_en_US.xml");
    this->initializeFromXml("../resources/xml/menus/NavigationMenu_en_US.xml");
}

BoxController::~BoxController()
{
    for (std::map< std::string, std::list< Box const * > >::const_iterator it = this->_patterns.begin(), end = this->_patterns.end();
    it != end; ++it)
    {
	std::for_each(it->second.begin(), it->second.end(), Ceg::DeleteObject());
    }
    for (std::map< std::string, std::list< Box const * > >::const_iterator it = this->_menus.begin(), end = this->_menus.end();
    it != end; ++it)
    {
	std::for_each(it->second.begin(), it->second.end(), Ceg::DeleteObject());
    }
}

/************************************************* [ GETTERS ] *************************************************/

void BoxController::getChildren(std::list<QGraphicsRectItem *> & graphicItems, Box const * box) const
{
    std::list<Box const *> childrenBox;
    if (box->getBoxType() == DEFAULT_BOX && box->getLevel() < 8) // mode par default, on limite la profondeur en mode par defaut a 8
    {
	this->calcChildren(childrenBox, box->getGeometry(), box->getLevel() + 1);
    }
    else // mode custom
    {
	childrenBox = box->getChilden();
    }
    this->createGraphicItems(graphicItems, childrenBox);
}

void BoxController::getParent(std::list<QGraphicsRectItem *> & graphicItems, Box const * box) const
{
    std::list<Box const *> childrenBox;
    if (box->getBoxType() == DEFAULT_BOX) // mode par default
    {
	this->calcParent(childrenBox, box);
    }
    else // mode custom
    {
	Box const * parentBox = box->getParent();
	if (parentBox != 0)
	{
	    if (parentBox->getParent() != 0) // On n'est pas au niveau 0
		childrenBox = box->getParent()->getChilden(); // pas tres ecolo, copie d une liste :(
	    else
		childrenBox = this->getPattern(parentBox);
	}

    }
    this->createGraphicItems(graphicItems, childrenBox);
}

//! This method uses window name to get all Box[es] (got initially from XML).
//! The list of AbstractBox is used to generate Item objects which is an area of the view.
void    BoxController::getPattern(Ceg::Window const & aWindow, std::list<QGraphicsRectItem *> & graphicItems) const
{
    std::map<std::string, std::list<Box const *> >::const_iterator  itFind = this->_patterns.find(aWindow.getProgramName());
    std::list<Box const *> childrenBox;

#ifndef Q_WS_WIN
    LOG4CXX_INFO(this->_logger, "Schema pour '" << aWindow.getProgramName() << "' demande");
#endif

    if (itFind != this->_patterns.end())
    {
#ifndef Q_WS_WIN
	LOG4CXX_INFO(this->_logger, "Configuration trouvee, chargement du schema");
#endif
	childrenBox = itFind->second;
    }
    else
    {
#ifndef Q_WS_WIN
	LOG4CXX_WARN(this->_logger, "Pas de configuration pour le programme, chargement du schema par defaut");
#endif
	this->calcChildren(childrenBox, aWindow.getGeometry(), 0);
    }
    this->createGraphicItems(graphicItems, childrenBox);
}

std::list<Box const *>    BoxController::getPattern(Box const * boxSearch) const
{
    for (std::map< std::string, std::list< Box const * > >::const_iterator it = this->_patterns.begin(), end = this->_patterns.end();
    it != end; ++it)
    {
	std::list< Box const * >::const_iterator itFind= std::find(it->second.begin(), it->second.end(), boxSearch);
	if (itFind != it->second.end())
	    return (it->second);

    }
    return (std::list<Box const *>());
}

void	BoxController::getMenu(std::string const & idMenu, std::list<QGraphicsRectItem *> & menuItems) const
{
#ifndef Q_WS_WIN
    LOG4CXX_INFO(this->_logger, "Menu - id(" << idMenu << ") demande");
#endif

    std::map<std::string, std::list<Box const *> >::const_iterator  itFind = this->_menus.find(idMenu);
    if (itFind != this->_menus.end())
    {
	this->createGraphicItems(menuItems, itFind->second);
    }
    else
    {
#ifndef Q_WS_WIN
	LOG4CXX_WARN(this->_logger, "Menu inconnu");
#endif
    }
}

/************************************************* [ OTHERS ] *************************************************/

//! This method is used in the case we are using a grid view,
//! indeed it is going to calculate position and size of each
//! grid areas in function of _nbGrid static value.
void BoxController::calcChildren(std::list<Box const *> & boxs, QRect const & geometry, unsigned short level) const
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
	    boxs.push_back(new Box(DEFAULT_BOX, level, QRect(x, y, tmpWidth, tmpHeight)));
	    x += tmpWidth;
	}
	y += tmpHeight;
    }
}

void BoxController::calcParent(std::list<Box const *> & boxs, Box const * item) const
{
    QDesktopWidget *desktop = QApplication::desktop();
    int level = item->getLevel();

    if (level == 0)
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

void BoxController::createGraphicItems(std::list<QGraphicsRectItem *> & graphicItems, std::list<Box const *> const & boxs) const
{
    for (std::list<Box const *>::const_iterator it = boxs.begin(), itEnd = boxs.end(); it != itEnd; ++it)
    {
	graphicItems.push_back(GraphicItemFactory::create(*it));
    }
}

void	BoxController::initializeFromConfig(QString const & directoryName)
{
    QDir    directory(directoryName);

    if (directory.exists() == true)
    {
	QFileInfoList const & files = directory.entryInfoList(QStringList("*.xml"));
	for (QFileInfoList::const_iterator it = files.begin(), itEnd = files.end();
	it != itEnd; ++it)
	{
	    this->initializeFromXml(it->absoluteFilePath());
	}
    }
    else
    {
#ifndef Q_WS_WIN
	LOG4CXX_WARN(this->_logger, directoryName.toStdString() << " doesn't exist");
#endif
    }
}

void    BoxController::initializeFromXml(QString const & fileName)
{
#ifndef Q_WS_WIN
    LOG4CXX_INFO(this->_logger, "Tentative de chargement du fichier : '" << fileName.toStdString() << "'");
#endif

    QFile	file(fileName);
    QDomDocument doc(fileName);

    QString  errorMsg;
    int  errorLine = 0, errorColumn = 0;
    if (file.open(QIODevice::ReadOnly) == true  &&  doc.setContent(&file, &errorMsg, &errorLine, &errorColumn) == true)
    {
#ifndef Q_WS_WIN
	LOG4CXX_INFO(this->_logger, "Chargement reussi");
#endif

	file.close();
	QDomElement const & rootElement = doc.documentElement();
	if (rootElement.tagName() == "boxes" || rootElement.tagName() == "menu")
	{
	    std::string const & programId = rootElement.attribute("id").toStdString();
	    std::list<Box const *> boxes;

#ifndef Q_WS_WIN
	    LOG4CXX_INFO(this->_logger, rootElement.tagName().toStdString() << " - Id '" << programId << "'");
#endif

	    for (QDomNode boxNode = rootElement.firstChild(); !boxNode.isNull(); boxNode = boxNode.nextSibling())
	    {
		QDomElement const & boxElement = boxNode.toElement();
		if (boxElement.isNull() == false && boxElement.tagName() == "box")
		{
		    boxes.push_back(new Box(boxElement, 0));
		}
	    }
	    if (boxes.empty() == false)
	    {
		if (rootElement.tagName() == "boxes")
		    this->_patterns.insert(std::make_pair(programId, boxes));
		else
		    this->_menus.insert(std::make_pair(programId, boxes));
	    }
	}
    }
    else
    {
	QFileInfo fileInfo(fileName);
#ifndef Q_WS_WIN
	LOG4CXX_ERROR(this->_logger, "Echec du chargement du fichier : " << fileInfo.absoluteFilePath().toStdString() << "\nRaison " << errorMsg.toStdString() << " at line = "<< errorLine << " - column = " << errorColumn);
#endif
    }
}
