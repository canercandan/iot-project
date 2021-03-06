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
/*********************************/
#include "PopMenuAction.h"
/*********************************/
#include "MainController.h"
#include "Menu.h"
/*********************************/
#include "Logger.h"

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * PopMenuAction::IDENTIFIER = "PopMenu";

PopMenuAction::PopMenuAction(QString const & menuId) :
	_menuId(menuId)
{
    Logger::getInstance()->log(DEBUG_LOG, "PopMenuAction::PopMenuAction(QString const & menuId)");
}

PopMenuAction::PopMenuAction(QDomElement const & domElement) :
	_menuId()
{
    Logger::getInstance()->log(DEBUG_LOG, "PopMenuAction::PopMenuAction(QDomElement const & domElement)");
    this->initializeFromXml(domElement);
}

void	PopMenuAction::initializeFromXml(QDomElement const & domElement)
{
    this->_menuId = domElement.attribute("MenuId");
}

/************************************************* [ OTHERS ] *************************************************/

void	PopMenuAction::exec(MainController & mainC)
{
    Logger::getInstance()->log(DEBUG_LOG, "PopMenuAction::exec");
    // Recuperation des items du menu
    AbstractScene * menuFind = mainC.getScene(this->_menuId); // On regarde si le menu est deja creer
    if (menuFind != 0 && menuFind->getType() == MENU_BOX)
    {
        menuFind->resetFocusItem();
        mainC.pushFrontScene(menuFind);
    }
    else
    {
        BoxController const & boxC = mainC.getBoxController();
        QList<QGraphicsRectItem *> menuItems;
        boxC.getMenu(this->_menuId, menuItems);
        if (menuItems.empty() == false)
        {
            // Creation du Menu avec les items recuperes
            Menu * menuScene = new Menu(this->_menuId);
            menuScene->initialize(menuItems);
            // affichage du menu
            mainC.pushFrontScene(menuScene);
        }
    }
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciatePopMenuAction(QDomElement const & domElement)
{
    return (new PopMenuAction(domElement));
}
