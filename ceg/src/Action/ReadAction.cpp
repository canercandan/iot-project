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
#include "ReadAction.h"
/*********************************/
#include "MainController.h"
#include "Utils.h"
/*********************************/
#include "Logger.h"

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * ReadAction::IDENTIFIER = "Read";

ReadAction::ReadAction(const QDomElement & actionElement) : _hideTime(1000)
{
    Logger::getInstance()->log(DEBUG_LOG, "ReadAction::ReadAction(const QDomElement & actionElement)");
    this->initializeFromXml(actionElement);
}

void ReadAction::initializeFromXml(const QDomElement & domElement)
{
    if (domElement.hasAttribute("time"))
    {
        this->_hideTime = domElement.attribute("time").toULong();
    }
}

/************************************************* [ OTHERS ] *************************************************/

void	ReadAction::exec(MainController & lm)
{
    Logger::getInstance()->log(DEBUG_LOG, "ReadAction::exec");
    View & view = lm.getView();

    view.hide();

    if (this->_hideTime > 0)
    {
        SleeperThread::msleep(this->_hideTime);
    }

    view.show();
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateReadAction(const QDomElement & actionElement)
{
    return (new ReadAction(actionElement));
}
