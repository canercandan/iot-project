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

#include <QtXml>
#include <QtXmlPatterns>
#include <QDebug>

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
        _patterns(), _menus()
{
    Logger::getInstance()->log(INFO_LOG, "Tentative de chargement des fichiers xml pour les menus");
    this->loadConfig("menus/");
    Logger::getInstance()->log(INFO_LOG, "Tentative de chargement des fichiers xml pour les programmes");
    this->loadConfig("boxes/");
}

BoxController::~BoxController()
{
    for (QMap< QString, QList< Box const * > >::const_iterator it = this->_patterns.begin(), end = this->_patterns.end();
    it != end; ++it)
    {
        std::for_each(it.value().begin(), it.value().end(), Ceg::DeleteObject());
    }
    for (QMap< QString, QList< Box const * > >::const_iterator it = this->_menus.begin(), end = this->_menus.end();
    it != end; ++it)
    {
        std::for_each(it.value().begin(), it.value().end(), Ceg::DeleteObject());
    }
}

/************************************************* [ GETTERS ] *************************************************/

bool BoxController::isZoomable(unsigned short level) const
{
    QSettings settings;
    int nbSquare = settings.value("general/squareNumber").toInt();
    int value = 7 - nbSquare;
    return (level < ((value < 1) ? 1 : value));
}

void BoxController::getChildren(QList<QGraphicsRectItem *> & graphicItems, Box const * box) const
{
    QList<Box const *> childrenBox;
    if (box->getBoxType() == DEFAULT_BOX && this->isZoomable(box->getLevel()) == true) // mode par default
    {
	this->calcChildren(childrenBox, box->getGeometry(), box->getLevel() + 1);
    }
    else if(box->getBoxType() == CUSTOM_BOX) // mode custom
    {
	childrenBox = box->getChilden();
    }
    this->createGraphicItems(graphicItems, childrenBox);
}

void BoxController::getParent(QList<QGraphicsRectItem *> & graphicItems, Box const * box) const
{
    QList<Box const *> childrenBox;
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
void    BoxController::getPattern(Ceg::Window const & aWindow, QList<QGraphicsRectItem *> & graphicItems) const
{
    QMap<QString, QList<Box const *> >::const_iterator  itFind = this->_patterns.find(aWindow.getProgramName().toLower());
    QList<Box const *> childrenBox;
    QString msg("Schema for '");
    msg += aWindow.getProgramName();
    msg += "' asked";
    Logger::getInstance()->log(INFO_LOG, msg);
    if (itFind != this->_patterns.end())
    {
	Logger::getInstance()->log(INFO_LOG, "Configuration found, schema loading");
        childrenBox = itFind.value();
    }
    else
    {
	Logger::getInstance()->log(WARNING_LOG,"No configuration found for this program, loading the default schema");
	this->calcChildren(childrenBox, aWindow.getGeometry(), 0);
    }
    this->createGraphicItems(graphicItems, childrenBox);
}

QList<Box const *>    BoxController::getPattern(Box const * boxSearch) const
{
    for (QMap< QString, QList< Box const * > >::const_iterator it = this->_patterns.begin(), end = this->_patterns.end();
    it != end; ++it)
    {
        QList< Box const * >::const_iterator itFind= std::find(it.value().begin(), it.value().end(), boxSearch);
        if (itFind != it.value().end())
            return (it.value());
    }
    return (QList<Box const *>());
}

void	BoxController::getMenu(QString const & idMenu, QList<QGraphicsRectItem *> & menuItems) const
{
    QString msg("Menu - id(");
    msg += idMenu;
    msg += ") asked";
    Logger::getInstance()->log(INFO_LOG, msg);

    QMap<QString, QList<Box const *> >::const_iterator  itFind = this->_menus.find(idMenu);
    if (itFind != this->_menus.end())
    {
        this->createGraphicItems(menuItems, itFind.value());
    }
    else
    {
        Logger::getInstance()->log(WARNING_LOG, "Unknown menu");
    }
}

/************************************************* [ OTHERS ] *************************************************/

//! This method is used in the case we are using a grid view,
//! indeed it is going to calculate position and size of each
//! grid areas in function of _nbGrid static value.
void BoxController::calcChildren(QList<Box const *> & boxs, QRect const & geometry, unsigned short level) const
{
    QSettings settings;
    int nbSquare = settings.value("general/squareNumber").toInt();
    int tmpWidth = geometry.width() / nbSquare;
    int tmpHeight = geometry.height() / nbSquare;
    int rows = 0;
    int y = geometry.y();

    while (rows++ < nbSquare)
    {
	int cols = 0;
	qreal x = geometry.x();
	while (cols++ < nbSquare)
	{
	    boxs.push_back(new Box(level, QRect(x, y, tmpWidth, tmpHeight)));
	    x += tmpWidth;
	}
	y += tmpHeight;
    }
}

void BoxController::calcParent(QList<Box const *> & boxs, Box const * item) const
{
    QSettings settings;
    int nbSquare = settings.value("general/squareNumber").toInt();
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
	width /= nbSquare;
    }
    int height = desktop->height();
    for (int i = 0; i < level; ++i)
    {
	height /= nbSquare;
    }

    int posXtop = 0;
    int posYtop = 0;
    int dynamicHeight = desktop->height() / nbSquare;
    int maxHeight = item->getGeometry().y() + item->getGeometry().height();
    for (int i = 0; i < level; ++i)
    {
	while ((posYtop + dynamicHeight) < maxHeight)
	{
	    posYtop += dynamicHeight;
	}
	dynamicHeight /= nbSquare;
    }

    int dynamicWidth = desktop->width() / nbSquare;
    int maxWidth = item->getGeometry().x() + item->getGeometry().width();
    for (int i = 0; i < level; ++i)
    {
	while ((posXtop + dynamicWidth) < maxWidth)
	{
	    posXtop += dynamicWidth;
	}
	dynamicWidth /= nbSquare;
    }
    this->calcChildren(boxs, QRect(posXtop, posYtop, width, height), item->getLevel() - 1);
}

void BoxController::createGraphicItems(QList<QGraphicsRectItem *> & graphicItems, QList<Box const *> const & boxs) const
{
    for (QList<Box const *>::const_iterator it = boxs.begin(), itEnd = boxs.end(); it != itEnd; ++it)
    {
	graphicItems.push_back(GraphicItemFactory::create(*it));
    }
}

void BoxController::loadConfig(QString const & typeSearch)
{
    QStringList	pathsToSearch;

#if defined(Q_OS_UNIX) || defined(Q_OS_MAC)
    pathsToSearch << "/usr/share/ceg/config";
    pathsToSearch << QCoreApplication::applicationDirPath() + "/share/ceg/config";
#elif defined(Q_OS_WIN)
    pathsToSearch << QCoreApplication::applicationDirPath() + "/../share/ceg/config";
    pathsToSearch << QCoreApplication::applicationDirPath() + "/../config";
#endif

    for (QStringList::const_iterator it = pathsToSearch.constBegin(), itEnd = pathsToSearch.end(); it != itEnd; ++it)
    {
	QDir    directory(*it + "/" + typeSearch);
	if (directory.exists() == true)
	{
	    this->initializeFromConfig(directory);
	    break;
	}
	else
	{
	    QString msg(directory.absolutePath());
	    msg += " doesn't exist";
	    Logger::getInstance()->log(WARNING_LOG, msg);
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

void	BoxController::validXml(QString const & xml_path)
{
    QStringList	pathsToSearch;
#if defined(Q_OS_UNIX) || defined(Q_OS_MAC)
    pathsToSearch << "/usr/share/ceg/common";
    pathsToSearch << QCoreApplication::applicationDirPath() + "/share/ceg/common";
#elif defined(Q_OS_WIN)
    pathsToSearch << QCoreApplication::applicationDirPath() + "/../share/ceg/common";
    pathsToSearch << QCoreApplication::applicationDirPath() + "/../common";
#endif

    QString schema_path;
    for (QStringList::const_iterator it = pathsToSearch.constBegin(), itEnd = pathsToSearch.end(); it != itEnd; ++it)
	{
	    if ( QFile::exists( *it + "/schema.xsd" ) == false ) { continue; }

	    schema_path = QString( *it + "/schema.xsd" );
	    break;
	}

    if ( schema_path.isEmpty() )
	{
	    Logger::getInstance()->log(ERROR_LOG, "schema.xsd not found");
	    return;
	}

    QUrl schemaUrl( schema_path );
    QXmlSchema schema;
    schema.load( schemaUrl );

    if ( !schema.isValid() )
	{
	    Logger::getInstance()->log(ERROR_LOG, "schema.xsd not valid");
	    return;
	}

    QFile file( xml_path );
    file.open( QIODevice::ReadOnly );

    QXmlSchemaValidator validator( schema );
    if ( validator.validate( &file, QUrl::fromLocalFile( file.fileName() ) ) == false )
	{
	    Logger::getInstance()->log(ERROR_LOG, "xml file not valid");
	}
}

void    BoxController::initializeFromXml(QString const & fileName)
{
    validXml( fileName );

    QString msg("Trying to load file: ");
    msg += fileName;
    Logger::getInstance()->log(INFO_LOG, msg);
    QFile	file(fileName);
    QDomDocument doc(fileName);

    QString  errorMsg;
    int  errorLine = 0, errorColumn = 0;
    if (file.open(QIODevice::ReadOnly) == true  &&  doc.setContent(&file, &errorMsg, &errorLine, &errorColumn) == true)
    {
	Logger::getInstance()->log(INFO_LOG, "Loading succeeded");
	file.close();
	QDomElement const & rootElement = doc.documentElement();
	if (rootElement.tagName() == "boxes" || rootElement.tagName() == "menu")
	{
	    QString msg(rootElement.tagName());
	    QString progId(rootElement.attribute("id"));
	    msg += " Id: "; msg += progId;
	    Logger::getInstance()->log(INFO_LOG, msg);
            QList<Box const *> boxes;
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
                    this->_patterns.insert(progId, boxes);
		else
                    this->_menus.insert(progId, boxes);
	    }
	}
    }
    else
    {
	QFileInfo fileInfo(fileName);
	QString msg("Fail during file loading : ");
	msg += fileInfo.absoluteFilePath();
        msg += "\nCause ";
        msg += errorMsg;
        msg += " at line = ";
        msg += errorLine;
        msg += " - column = ";
        msg += errorColumn;
	Logger::getInstance()->log(ERROR_LOG, msg);
    }
}
