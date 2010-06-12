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
#include "ClickAction.h"
/*********************************/
#include "ActionFactory.h"
#include "AbstractItem.h"
#include "Box.h"
#include "MainController.h"
#include "AbstractScene.h"
#include "ICommunicationGraphicalServer.h"
#include "Utils.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

ClickAction::ClickAction(const QDomElement & actionElement)
{
    this->initializeFromXml(actionElement);
}

/************************************************* [ OTHERS ] *************************************************/

bool	ClickAction::exec(MainController & lm)
{
    AbstractItem const * ai = lm.getCurrentScene()->getCurrentItem();
    Box const *	ab = ai->getBox();

    if (ab == 0)
	return (false);

    QCursor::setPos(ab->getGeometry().center());

    lm.getView().hide();

    switch (this->_type)
    {
    case LeftClick:
    case MiddleClick:
    case RightClick:
	lm.getComGs()->generateClickEvent(this->_type);
	break;
    case LeftDbClick:
	lm.getComGs()->generateClickEvent(LeftClick);
	lm.getComGs()->generateClickEvent(LeftClick);
	break;
    default:
	break;
    }

    SleeperThread::msleep(1000);

    lm.getView().show();

    return (true);
}

void ClickAction::initializeFromXml(const QDomElement &)
{

}

IAction * instanciateClickAction(QDomElement const & actionElement)
{
    return (new ClickAction(actionElement));
}
