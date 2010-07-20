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
#include <QKeyEvent>
#include <QIcon>
/*********************************/
#include "View.h"
/*********************************/
#include "MainController.h"
#include "MoveAction.h"
#include "ClickAction.h"
#include "AbstractScene.h"
#include "Systray.h"
#include "ValidAction.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

View::View(MainController & lm, Systray & systray)
    : _lm(lm)
{
    this->setWindowOpacity(0.5);
    this->setWindowIcon(QIcon(":/images/systray-transparent-32x32.png"));

    QObject::connect(this, SIGNAL(actionEmitted(IAction&)),&lm, SLOT(on_action_emitted(IAction&)));
    QObject::connect(this, SIGNAL(triggered()),&systray, SLOT(on__startAction_triggered()));
}

/************************************************* [ OTHERS ] *************************************************/

void	View::initialize()
{
    AbstractScene* as = this->_lm.getCurrentScene();
    this->setScene(as);
    this->setGeometry(as->getGeometry());

    //-----------------------------------------------------------------------------
    // Remove the title bar
    //-----------------------------------------------------------------------------

    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    //-----------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    // The following line allows to keep scene view on top.
    // At this time it is not needed, perhaps in the future!
    //-----------------------------------------------------------------------------

    //this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

    //-----------------------------------------------------------------------------


    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWindowState(Qt::WindowFullScreen);


    //-----------------------------------------------------------------------------
    // Desactive les interactions (clic) sur la vue
    //-----------------------------------------------------------------------------

    this->setInteractive(false);

    //-----------------------------------------------------------------------------
}

void	View::keyPressEvent(QKeyEvent* keyEvent)
{
    int	key = keyEvent->key();
    switch (key)
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
	{
	    MoveAction action(key);
	    emit actionEmitted(action);
	}
	break;
    case Qt::Key_Return:
	{
	    ValidAction action;
	    emit actionEmitted(action);
	}
	break;
    default:
	break;
    }
}

void View::closeEvent(QCloseEvent *)
{
    emit triggered();
}
