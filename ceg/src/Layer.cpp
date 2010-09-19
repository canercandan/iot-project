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

/*********************************/
#include "AbstractItem.h"
#include "MainController.h"
/*********************************/
#include "Layer.h"
/*********************************/
#include "Box.h"
#include "CloseAction.h"
#include "PopMenuAction.h"
#include "Logger.h"
/*********************************/


/************************************************* [ CTOR/DTOR ] *************************************************/

Layer::Layer(Ceg::Window const & hostWindow, MainController & mainC) :
        AbstractScene(hostWindow.getProgramName(), 0), _host(hostWindow), _menuAction(0), _process(0), _mainC(mainC)
{
    QObject::connect(this, SIGNAL(actionEmitted(IAction&)),&this->_mainC, SLOT(on_action_emitted(IAction&)));
}

Layer::~Layer()
{
    delete this->_menuAction;
    if (this->_process != 0)
    {
        if (this->_process->state() != QProcess::NotRunning)
        {
            QObject::disconnect(this->_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(on_processError(QProcess::ProcessError)));
            QObject::disconnect(this->_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(on_processFinished(int,QProcess::ExitStatus)));
            this->_process->terminate();
            this->_process->waitForFinished();
        }
        delete this->_process;
    }
}

/************************************************* [ GETTERS ] *************************************************/

QRect  Layer::getGeometry() const
{
    return (this->_host.getGeometry());
}

void    Layer::setProcess(QProcess * process)
{
    this->_process = process;
    QObject::connect(this->_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(on_processError(QProcess::ProcessError)));
    QObject::connect(this->_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(on_processFinished(int,QProcess::ExitStatus)));
}

void    Layer::on_processError(QProcess::ProcessError)
{
    CloseAction action(this);
    emit actionEmitted(action);
}

void    Layer::on_processFinished(int, QProcess::ExitStatus)
{
    CloseAction action(this);
    emit actionEmitted(action);
}

/************************************************* [ OTHERS ] *************************************************/

void	Layer::initialize(QList<QGraphicsRectItem *> const & sceneItems)
{
    if (sceneItems.empty() == false)
    {
	this->_type = static_cast<AbstractItem *>(sceneItems.front())->getBox()->getBoxType();
	if (this->_menuAction == 0)
	{
	    this->_menuAction = new PopMenuAction("Navigation");
	}
    }
    AbstractScene::initialize(sceneItems);
}

IAction * Layer::keyPressEvent(int key)
{
    switch (key)
    {
    case Qt::Key_Left :
    case Qt::Key_Right :
	return (this->moveHorizontally());
	break;
    case Qt::Key_Up :
    case Qt::Key_Down :
	this->moveVertically();
	break;
    default:
	break;
    }
    return (0);
}

void	Layer::moveVertically() const
{
    QList<QGraphicsItem *> items =  this->items();
    int sizeList = items.size();
    QGraphicsItem * focusItem = this->focusItem();
    QList<QGraphicsItem *>::const_iterator it = items.begin();
    QList<QGraphicsItem *>::const_iterator tmpIt = it;

    int index = items.indexOf(focusItem);
    ++index;
    QRectF currentRectF = focusItem->boundingRect();
    currentRectF.setHeight(this->getGeometry().height());
    currentRectF.setWidth(currentRectF.width());
    currentRectF.setX(currentRectF.x());
    currentRectF.setY(0);

    int i = 0;
    bool haveRect = false;
    while (i < sizeList && haveRect == false)
    {
	index = ((index < sizeList) ? index : (index - sizeList));
	tmpIt = it;
	tmpIt += index;
	haveRect = currentRectF.intersects((*tmpIt)->boundingRect());
	++index;
	++i;
    }
    if (haveRect == true)
    {
	(*tmpIt)->setFocus();
    }
    else
    {
	index = items.indexOf(focusItem) + 1;
	index = ((index < sizeList) ? index : (index - sizeList));
	it += index;
	(*it)->setFocus();
    }
}

IAction *	Layer::moveHorizontally()
{
    bool printMenu = false;
    QList<QGraphicsItem *> items =  this->items();
    QList<QGraphicsItem *>::const_iterator it = items.begin();
    QGraphicsItem * focusItem = this->focusItem();
    int index = items.indexOf(focusItem);
    index++;
    if (index >= items.size())
    {
	printMenu = true;
	index = 0;
    }
    it += index;
    (*it)->setFocus();
    if (focusItem->boundingRect().x() > (*it)->boundingRect().x() || printMenu)
    {
	return (this->_menuAction);
    }
    return (0);
}
