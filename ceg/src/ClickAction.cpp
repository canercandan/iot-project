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

#include <iostream>

#include <QWaitCondition>
#include <QThread>

#include "ClickAction.h"

#include "AbstractItem.h"
#include "AbstractBox.h"
#include "LayerManager.h"
#include "AbstractScene.h"
#include "ICommunicationGraphicalServer.h"

class SleeperThread : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
	QThread::msleep(msecs);
    }
};

ClickAction::ClickAction(ClickType type /*= LeftClick*/)
    : _type(type)
{}

bool	ClickAction::exec(LayerManager& lm)
{
    AbstractItem* ai = lm.getCurrentLayer()->getCurrentItem();
    AbstractBox*	ab = ai->getBox();

    if (ab == NULL)
	return false;

    QCursor::setPos(ab->getGeometry().center());

    lm.getView()->hide();

    //SleeperThread::msleep(1000);

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

    lm.getView()->show();

    return true;
}
