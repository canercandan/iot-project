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
#include <iostream>
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
    : _mainC(lm)
{
    this->setWindowOpacity(0.5);
    this->setWindowIcon(QIcon(":/images/systray-transparent-32x32.png"));

    QObject::connect(this, SIGNAL(actionEmitted(IAction&)),&lm, SLOT(on_action_emitted(IAction&)));
    QObject::connect(this, SIGNAL(triggered()),&systray, SLOT(on__startAction_triggered()));
}

View::~View()
{
    std::cerr << "View::~View()" << std::endl;
}

/************************************************* [ OTHERS ] *************************************************/

void	View::initialize()
{
    AbstractScene* as = this->_mainC.getCurrentScene();
    this->setScene(as);
    this->setGeometry(as->getGeometry());
    this->setCacheMode(QGraphicsView::CacheNone);

    // FramelessWindowHint : retire les bordures de la widget
    // WindowStaysOnTopHint : la fenetre reste au top niveau
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    //-----------------------------------------------------------------------------

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWindowState(Qt::WindowFullScreen);

    //-----------------------------------------------------------------------------
    // Desactive les interactions (clic) sur la vue
    //-----------------------------------------------------------------------------

    this->setInteractive(false);

    this->activateWindow();
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
