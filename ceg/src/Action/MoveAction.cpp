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
#include <QDebug>
/*********************************/
#include "MoveAction.h"
/*********************************/
#include "MainController.h"
#include "AbstractScene.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * MoveAction::IDENTIFIER = "Move";

MoveAction::MoveAction(int key) :
	_key(key)
{
    qDebug() << "MoveAction::MoveAction(int key)";
}

MoveAction::MoveAction(const QDomElement & actionElement) :
	_key(0)
{
    qDebug() << "MoveAction::MoveAction(const QDomElement & actionElement)";
    this->initializeFromXml(actionElement);
}

void MoveAction::initializeFromXml(const QDomElement &)
{

}

/************************************************* [ OTHERS ] *************************************************/

bool	MoveAction::exec(MainController & lm)
{
    qDebug() << "MoveAction::exec";
    IAction * action = lm.getCurrentScene()->keyPressEvent(this->_key);
    if (action != 0)
	return (action->exec(lm));
    return (true);
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateMoveAction(const QDomElement & actionElement)
{
    return (new MoveAction(actionElement));
}