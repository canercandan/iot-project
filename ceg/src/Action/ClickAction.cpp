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

char const * ClickAction::IDENTIFIER = "Click";

ClickAction::ClickAction(const QDomElement & actionElement) : _type(1)
{
    qDebug() << "ClickAction::ClickAction";
    this->initializeFromXml(actionElement);
}

void ClickAction::initializeFromXml(const QDomElement & domElement)
{
    this->_type = domElement.attribute("type").toInt();
}

/************************************************* [ OTHERS ] *************************************************/

void	ClickAction::exec(MainController & lm)
{
    qDebug() << "ClickAction::exec";
    AbstractItem const * ai = lm.getSceneAt(static_cast<size_t>(2))->getCurrentItem();
    Box const *	ab = ai->getBox();

    if (ab == 0)
        return ;

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
        lm.getComGs()->generateClickEvent(this->_type);
        lm.getComGs()->generateClickEvent(this->_type);
	break;
    default:
	break;
    }

    SleeperThread::msleep(1000);

    lm.getView().show();
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateClickAction(QDomElement const & actionElement)
{
    return (new ClickAction(actionElement));
}
