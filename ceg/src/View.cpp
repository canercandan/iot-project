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
#include <QDebug>
/*********************************/
#include "View.h"
/*********************************/
#include "MainController.h"
#include "MoveAction.h"
#include "ClickAction.h"
#include "AbstractScene.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

View::View(MainController & lm)
    : _lm(lm)
{
    // QObject::connect(this, SIGNAL(actionEmitted(IAction &)),&lm, SLOT(onActionEmitted(IAction&)));
     this->setWindowOpacity(0.5);
}

View::~View()
{
    qDebug() << "View::~View()";
}

/************************************************* [ OTHERS ] *************************************************/

void	View::initialize()
{
    AbstractScene* as = this->_lm.getCurrentScene();
    this->setScene(as);
    this->setGeometry(as->getGeometry());
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint); // Enleve la title bar
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWindowState(Qt::WindowFullScreen);
    this->setInteractive(false); // Desactive les interactions (clic) sur la vue
}

void	View::keyPressEvent(QKeyEvent* keyEvent)
{

    int	key = keyEvent->key();
    qDebug() << "Touche clavier utilisee : " << key;
    switch (key)
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Return:
    case Qt::Key_Backspace:
	{
	    MoveAction a(key);
            //this->_lm.actionHandler(a);
	}
	break;
    default:
	break;
    }
}
