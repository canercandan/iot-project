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

#include <QKeyEvent>

#include "View.h"
#include "LayerManager.h"
#include "MoveAction.h"
#include "ClickAction.h"
#include "AbstractScene.h"

View::View(LayerManager* lm)
    : _lm(lm)
{}

void	View::init()
{
  AbstractScene* as = _lm->getCurrentLayer();
  this->setScene(as);
  WindowGeometry geo = as->getGeometry();
  this->setGeometry(geo._x, geo._y, geo._width, geo._height);
  this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  //this->setFocusPolicy(Qt::WheelFocus);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setWindowState(Qt::WindowFullScreen);
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
    case Qt::Key_Return:
    case Qt::Key_Backspace:
      {
	MoveAction a(key);
	this->_lm->actionHandler(a);
      }
      break;
    case Qt::Key_0:
      {
	ClickAction a;
	this->_lm->actionHandler(a);
      }
      break;
    case Qt::Key_1:
      {
	ClickAction a(ClickAction::LeftDbClick);
	this->_lm->actionHandler(a);
      }
      break;
    default:
      break;
    }
}
