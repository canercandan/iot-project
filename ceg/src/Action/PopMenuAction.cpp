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
#include <QDomElement>
#include <QDebug>
/*********************************/
#include "PopMenuAction.h"
/*********************************/
#include "MainController.h"
#include "Menu.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * PopMenuAction::IDENTIFIER = "PopMenu";

PopMenuAction::PopMenuAction(std::string const & menuId) :
	_menuId(menuId)
{
    qDebug() << "PopMenuAction::PopMenuAction(std::string const & menuId)";
}

PopMenuAction::PopMenuAction(QDomElement const & domElement) :
	_menuId()
{
    qDebug() << "PopMenuAction::PopMenuAction(QDomElement const & domElement)";
    this->initializeFromXml(domElement);
}

void	PopMenuAction::initializeFromXml(QDomElement const & domElement)
{
    this->_menuId = domElement.attribute("MenuId").toStdString();
}

/************************************************* [ OTHERS ] *************************************************/

bool	PopMenuAction::exec(MainController & mainC)
{
    qDebug() << "PopMenuAction::exec";
    // Recuperation des items du menu
    BoxController const & boxC = mainC.getBoxController();
    std::list<QGraphicsRectItem *> menuItems;
    boxC.getMenu(this->_menuId, menuItems);
    // Creation du Menu avec les items recuperes
    Menu * menuScene = new Menu;
    menuScene->initialize(menuItems);
    // affichage du menu
    mainC.pushFrontScene(menuScene);
    return (true);
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciatePopMenuAction(QDomElement const & domElement)
{
    return (new PopMenuAction(domElement));
}
