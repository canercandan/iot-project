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

#include <QApplication>
#include <QDesktopWidget>

#include "LayerManager.h"

#include "Layer.h" // debug
#include "Window.h" // debug
#include "BoxManager.h"
#include "IAction.h"
#ifdef _WIN32
#include "Win32Explorer.h"
#else
#include "XWindowSystem.h"
#endif

/************************************************* [ CTOR/DTOR ] *************************************************/

LayerManager::LayerManager() :
  _view(*this), _layers(),_currentLayer(), _boxManager(),
#ifdef _WIN32
	_comGs(new Win32Explorer)
#else
	_comGs(new XWindowSystem)
#endif
{
}

LayerManager::~LayerManager()
{
    for (std::list<AbstractScene*>::const_iterator it = this->_layers.begin(), end = this->_layers.end(); it != end; ++it)
    {
	delete *it;
    }

    delete this->_comGs;
}

/************************************************* [ GETTERS ] *************************************************/

BoxManager const &	LayerManager::getBoxManager() const
{
    return (this->_boxManager);
}

ICommunicationGraphicalServer *	LayerManager::getComGs() const
{
    return (this->_comGs);
}

AbstractScene*	LayerManager::getCurrentLayer() const
{
    return (*this->_currentLayer);
}

View &	LayerManager::getView()
{
    return (this->_view);
}

/************************************************* [ OTHERS ] *************************************************/

bool    LayerManager::actionHandler(IAction & anAction)
{
    return (anAction.exec(*this));
}

void LayerManager::createLayers(std::list<Ceg::Window> const & windows)
{
    for (std::list<Ceg::Window>::const_iterator it = windows.begin(), itEnd = windows.end(); it != itEnd; ++it)
    {
	Layer * oneLayer = new Layer(*it);
	std::list<QGraphicsRectItem *> graphicItems;
	this->_boxManager.getPattern(*it, graphicItems);
	oneLayer->initScene(graphicItems);
	this->_layers.push_front(oneLayer);
    }
}

void LayerManager::init()
{
    std::list<Ceg::Window>  windows;
    //this->_comGs->getWindows(windows);

    QDesktopWidget *desktop = QApplication::desktop();
    windows.push_back(Ceg::Window(0, QRect(0 , 0, desktop->width(), desktop->height())));

    this->createLayers(windows);
    this->_currentLayer = this->_layers.begin();
}

void LayerManager::start()
{
    this->init();
    this->_view.init();
    this->_view.show();
}
