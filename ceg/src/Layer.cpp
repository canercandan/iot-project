// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyleft (C) 2010 CEG development team
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

#include "AbstractItem.h"
#include "Layer.h"
#include "ZoomAction.h" // debug
Layer::Layer(Ceg::Window const & hostWindow) :
	AbstractScene(hostWindow.getGeometry().x(), hostWindow.getGeometry().y(), hostWindow.getGeometry().width(), hostWindow.getGeometry().height()),
	_host(hostWindow)
{
}

QRect  Layer::getGeometry() const
{
    return (this->_host.getGeometry());
}

IAction * Layer::keyPressEvent(int key)
{
  switch (key)
    {
    case Qt::Key_Left :
      {
	this->_moveHorizontally();
	break;
      }
    case Qt::Key_Right :
      {
	this->_moveHorizontally();
	break;
      }
    case Qt::Key_Up :
      {
	this->_moveVertically();
	break;
      }
    case Qt::Key_Down :
      {
	this->_moveVertically();
 	break;
      }
    case Qt::Key_Return :
      {
	AbstractItem * focusItem = static_cast<AbstractItem *>(this->focusItem());
	return (focusItem->onEvent());
      }
      break;
    case Qt::Key_Backspace :
	return (new ZoomAction(false));
	break;
    }
    return (0);
}

//chris, yann => Methodes temporaires, se servir des IActions par la suite
void	Layer::_moveVertically() const
{
  QList<QGraphicsItem *> items =  this->items();
  QGraphicsItem * focusItem = this->focusItem();
  QList<QGraphicsItem *>::iterator it = items.begin();
  QList<QGraphicsItem *>::iterator tmpIt = it;
  QRectF currentRectF = focusItem->boundingRect();
  QRectF tmpRectF;
  int sizeList = items.size();
  int index = items.indexOf(focusItem);
  int i = 0;
  bool haveRect = false;

  index++;
  currentRectF.setHeight(this->getGeometry().height());
  currentRectF.setWidth(currentRectF.width());
  currentRectF.setX(currentRectF.x());
  currentRectF.setY(0);
  while (i < sizeList && !haveRect)
  {
      index = ((index < sizeList) ? index : (index - sizeList));
      tmpIt = it;
      tmpIt += index;
      tmpRectF = (*tmpIt)->boundingRect();
      if (currentRectF.intersects(tmpRectF))
          haveRect = true;
      index++;
      i++;
  }
  if (haveRect)
      (*tmpIt)->setFocus();
  else
  {
      index = items.indexOf(focusItem) + 1;
      index = ((index < sizeList) ? index : (index - sizeList));
      it += index;
      (*it)->setFocus();
  }

}

#include <QDebug>

//chris, yann => Methodes temporaires, se servir des IActions par la suite
void	Layer::_moveHorizontally() const
{
// #if defined(Q_WS_WIN)
//   QList<QGraphicsItem *> items =  this->items();
//   QList<QGraphicsItem *>::iterator it = items.begin();
//   QGraphicsItem * focusItem = this->focusItem();
//   int sizeList = items.size();
//   int index = items.indexOf(focusItem);
//   ++index;
//   if (index < sizeList)
//     it += index;
//   (*it)->setFocus();
// #elif defined(Q_WS_X11)
   QList<QGraphicsItem *> items =  this->items();
   QList<QGraphicsItem *>::iterator it = items.begin();
   QGraphicsItem * focusItem = this->focusItem();
   int sizeList = items.size();
   int index = items.indexOf(focusItem);
   index++;
   if (index >= sizeList)
       index = 0;
   it += index;
   (*it)->setFocus();
   if (focusItem->x() > (*it)->x())
   {
     this->_printMenuEvent();
   }
  //#endif
}

// Methode qui va faire appel a l'affichage du menu !
void    Layer::_printMenuEvent() const
{}
