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
#include "KeyboardAction.h"
/*********************************/
#include "ActionFactory.h"
#include "AbstractItem.h"
#include "Box.h"
#include "MainController.h"
#include "AbstractScene.h"
#include "ICommunicationGraphicalServer.h"
#include "Utils.h"
#include "Logger.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * KeyboardAction::IDENTIFIER = "Keyboard";

KeyboardAction::KeyboardAction(const QDomElement & actionElement) : _key("")
{
    Logger::getInstance()->log(DEBUG_LOG, "KeyboardAction::KeyboardAction");
    this->initializeFromXml(actionElement);
}

void KeyboardAction::initializeFromXml(const QDomElement & domElement)
{
    if (domElement.hasAttribute("press") == true)
    this->_key = domElement.attribute("press");
}

/************************************************* [ OTHERS ] *************************************************/

void	KeyboardAction::exec(MainController & mainC)
{
    Logger::getInstance()->log(DEBUG_LOG, "KeyboardAction::exec");
    /*
    Explication pour la position, quand on est mode custom, l'action est lancee depuis la scene courante, dans le cas du
       mode par defaut, les actions sont lancees depuis les menus et ce sont les menus qui sont en scene courante
       */
    size_t position = (mainC.getCurrentScene()->getType() == CUSTOM_BOX) ? 1 : 2;
    AbstractScene * scene = mainC.getSceneAt(position);
    AbstractItem const * ai = scene->getCurrentItem();
    Box const *	ab = ai->getBox();

    if (ab == 0)
        return ;

    QCursor::setPos(ab->getGeometry().center());

    mainC.getView().hide();


    mainC.getComGs()->generateKeybdEvent(this->_key[0].toAscii());


   //SleeperThread::msleep(1000);

    mainC.getView().show();
    //mainC.getComGs()->generateClickEvent(1);
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateKeyboardAction(QDomElement const & actionElement)
{
    return (new KeyboardAction(actionElement));
}
