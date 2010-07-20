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
#include <QSettings>
#include <QLocale>
/*********************************/
#include "BoxController.h"
/*********************************/
#include "Box.h"
#include "Window.h"
#include "GraphicItemFactory.h"
#include "Utils.h"
#include "Logger.h"
/*********************************/


/************************************************* [ CTOR/DTOR ] *************************************************/

BoxController::BoxController() :
	_patterns(), _menus(), _nbSquare(3)
{
    Logger::getInstance()->Log(INFO, "Chargement des fichiers xml pour les programmes");
    Logger::getInstance()->Log(INFO, "Chargement des fichiers xml pour les menus");
    this->loadConfig("menus/");
    this->loadConfig("boxes/");

    QSettings settings;
    this->_nbSquare = settings.value("general/squareNumber").toInt();
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

bool BoxController::isZoomable(unsigned short level) const
{
    int value = 7 - this->_nbSquare;
    return (level < ((value < 1) ? 1 : value));
}

void BoxController::getChildren(std::list<QGraphicsRectItem *> & graphicItems, Box const * box) const
{
    std::list<Box const *> childrenBox;
    if (box->getBoxType() == DEFAULT_BOX && this->isZoomable(box->getLevel()) == true) // mode par default
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
    QString msg("Schema for '");
    msg += aWindow.getProgramName().c_str();
    msg += "' asked";
    Logger::getInstance()->Log(INFO, msg);
    if (itFind != this->_patterns.end())
    {
	Logger::getInstance()->Log(INFO, "Configuration found, schema loading");
	childrenBox = itFind->second;
    }
    else
    {
	Logger::getInstance()->Log(WARNING,"No configuration found for this program, loading the default schema");
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
    QString msg("Menu - id(");
    msg += idMenu.c_str();
    msg += ") asked";
    Logger::getInstance()->Log(INFO, msg);

    std::map<std::string, std::list<Box const *> >::const_iterator  itFind = this->_menus.find(idMenu);
    if (itFind != this->_menus.end())
    {
	this->createGraphicItems(menuItems, itFind->second);
    }
    else
    {
     Logger::getInstance()->Log(WARNING, "Unknown menu");
    }
}

/************************************************* [ OTHERS ] *************************************************/

//! This method is used in the case we are using a grid view,
//! indeed it is going to calculate position and size of each
//! grid areas in function of _nbGrid static value.
void BoxController::calcChildren(std::list<Box const *> & boxs, QRect const & geometry, unsigned short level) const
{
    int tmpWidth = geometry.width() / this->_nbSquare;
    int tmpHeight = geometry.height() / this->_nbSquare;
    int rows = 0;
    int y = geometry.y();

    while (rows++ < this->_nbSquare)
    {
	int cols = 0;
	qreal x = geometry.x();
	while (cols++ < this->_nbSquare)
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
	width /= this->_nbSquare;
    }
    int height = desktop->height();
    for (int i = 0; i < level; ++i)
    {
	height /= this->_nbSquare;
    }

    int posXtop = 0;
    int posYtop = 0;
    int dynamicHeight = desktop->height() / this->_nbSquare;
    int maxHeight = item->getGeometry().y() + item->getGeometry().height();
    for (int i = 0; i < level; ++i)
    {
	while ((posYtop + dynamicHeight) < maxHeight)
	{
	    posYtop += dynamicHeight;
	}
	dynamicHeight /= this->_nbSquare;
    }

    int dynamicWidth = desktop->width() / this->_nbSquare;
    int maxWidth = item->getGeometry().x() + item->getGeometry().width();
    for (int i = 0; i < level; ++i)
    {
	while ((posXtop + dynamicWidth) < maxWidth)
	{
	    posXtop += dynamicWidth;
	}
	dynamicWidth /= this->_nbSquare;
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

void BoxController::loadConfig(QString const & typeSearch)
{
    QSettings settings;
    QString language = settings.value("general/language").toString();
    QString directoryName = "/config/" + typeSearch + language;
    QStringList	pathsToSearch(QCoreApplication::applicationDirPath());
#if defined(Q_OS_UNIX)
    pathsToSearch << "/usr/share/ceg";
#elif defined(Q_OS_WIN)
    pathsToSearch << "../share/ceg";
#elif defined(Q_OS_MAC)
    // FIXME i don't know how do this on mac
    pathsToSearch << "../share/ceg";
#endif

    for (QStringList::const_iterator it = pathsToSearch.constBegin(), itEnd = pathsToSearch.end(); it != itEnd; ++it)
    {
	QDir    directory(*it + directoryName);
	if (directory.exists() == true)
	{
	    this->initializeFromConfig(directory);
	    break;
	}
	else
	{
	    QString msg(directory.absolutePath());
	    msg += " doesn't exist";
	    Logger::getInstance()->Log(WARNING, msg);
	}
    }
}

void	BoxController::initializeFromConfig(QDir const & directory)
{
    QFileInfoList const & files = directory.entryInfoList(QStringList("*.xml"));
    for (QFileInfoList::const_iterator it = files.begin(), itEnd = files.end();
    it != itEnd; ++it)
    {
	this->initializeFromXml(it->absoluteFilePath());
    }

}

void    BoxController::initializeFromXml(QString const & fileName)
{
    QString msg("Trying to load file: ");
    msg += fileName;
    Logger::getInstance()->Log(INFO, msg);
    QFile	file(fileName);
    QDomDocument doc(fileName);

    QString  errorMsg;
    int  errorLine = 0, errorColumn = 0;
    if (file.open(QIODevice::ReadOnly) == true  &&  doc.setContent(&file, &errorMsg, &errorLine, &errorColumn) == true)
    {
	Logger::getInstance()->Log(INFO, "Loading succeeded");
	file.close();
	QDomElement const & rootElement = doc.documentElement();
	if (rootElement.tagName() == "boxes" || rootElement.tagName() == "menu")
	{
	    QString msg(rootElement.tagName());
	    QString progId(rootElement.attribute("id"));
	    msg += " Id: "; msg += progId;
	    Logger::getInstance()->Log(INFO, msg);
	    std::list<Box const *> boxes;
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
		    this->_patterns.insert(std::make_pair(progId.toStdString(), boxes));
		else
		    this->_menus.insert(std::make_pair(progId.toStdString(), boxes));
	    }
	}
    }
    else
    {
	QFileInfo fileInfo(fileName);
	QString msg("Fail during file loading : ");
	msg += fileInfo.absoluteFilePath();
	msg += "\nCause "; msg += errorMsg;msg += " at line = "; msg += errorLine;
	msg += " - column = "; msg += errorColumn;
	Logger::getInstance()->Log(ERROR, msg);
    }
}
