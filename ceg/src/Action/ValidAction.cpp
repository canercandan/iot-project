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

#include "ValidAction.h"
/*********************************/
#include "AbstractItem.h"
#include "MainController.h"
#include "AbstractScene.h"
/*********************************/
#include "Logger.h"

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * ValidAction::IDENTIFIER = "Valid";

ValidAction::ValidAction()
{
    Logger::getInstance()->log(DEBUG_LOG, "ValidAction::ValidAction()");
}

ValidAction::ValidAction(const QDomElement &)
{
    Logger::getInstance()->log(DEBUG_LOG, "ValidAction::ValidAction(const QDomElement & actionElement)");
}

void ValidAction::initializeFromXml(const QDomElement &)
{

}

/************************************************* [ OTHERS ] *************************************************/

void	ValidAction::exec(MainController & mc)
{
    Logger::getInstance()->log(DEBUG_LOG, "ValidAction::exec");
    AbstractItem const * item = mc.getCurrentScene()->getCurrentItem();
    IAction * action = item->getEvent();
    if (action != 0)
        action->exec(mc);
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateValidAction(const QDomElement &)
{
    return (new ValidAction);
}
