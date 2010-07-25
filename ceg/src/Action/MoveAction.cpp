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
#include <QTextStream>
/*********************************/
#include "MoveAction.h"
/*********************************/
#include "MainController.h"
#include "AbstractScene.h"
/*********************************/
#include "Logger.h"
/************************************************* [ CTOR/DTOR ] *************************************************/

char const * MoveAction::IDENTIFIER = "Move";

MoveAction::MoveAction(int key) :
	_key(key)
{
   Logger::getInstance()->log(DEBUG_LOG, "MoveAction::MoveAction(int key)--");
}

MoveAction::MoveAction(const QDomElement & actionElement) :
        _key(Qt::Key_Left)
{
   Logger::getInstance()->log(DEBUG_LOG, "MoveAction::MoveAction(const QDomElement & actionElement)");
    this->initializeFromXml(actionElement);
}

void MoveAction::initializeFromXml(const QDomElement & domElement)
{
    this->_key = domElement.attribute("key").toInt();
}

/************************************************* [ OTHERS ] *************************************************/

void	MoveAction::exec(MainController & mainC)
{
    QString msg;
    QTextStream tmp(&msg);
    tmp << "MoveAction::exec " << this->_key;
    Logger::getInstance()->log(DEBUG_LOG, msg);

    IAction * action = mainC.getCurrentScene()->keyPressEvent(this->_key);
    if (action != 0)
    {
        action->exec(mainC);
    }
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateMoveAction(const QDomElement & actionElement)
{
    return (new MoveAction(actionElement));
}
