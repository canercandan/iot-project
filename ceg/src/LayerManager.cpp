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

#include <unistd.h> // for sleep, it is gonna be replaced by Qt sleep

#include <QtGui/QApplication> // debug
#include <QDesktopWidget>

#include "LayerManager.h"
#include "Layer.h" // debug
#include "Window.h" // debug

#ifdef _WIN32
#include "Win32Explorer.h"
#else
#include "XWindowSystem.h"
#endif

#include "MoveAction.h"

LayerManager::LayerManager() :
    _view(this), _boxManager(new BoxManager),
#ifdef _WIN32
	_comGs(new Win32Explorer)
#else
	_comGs(new XWindowSystem)
#endif
{
    this->_view.setWindowOpacity(0.5);
}

LayerManager::~LayerManager()
{
    for (std::list<AbstractScene*>::iterator
	 it = this->_layers.begin(),
	 end = this->_layers.end();
    it != end; ++it)
    {
	delete *it;
    }

    delete this->_boxManager;
    delete this->_comGs;
}

void LayerManager::init()
{
    std::list<Ceg::Window>  windows;
    //this->_comGs->getWindows(windows);

    QDesktopWidget *desktop = QApplication::desktop();
    windows.push_back(Ceg::Window(0, WindowGeometry(0 , 0, desktop->width(), desktop->height())));

    this->createLayers(windows);
    this->_currentLayer = this->_layers.begin();
}

void LayerManager::start()
{
    this->_view.setScene(*(this->_currentLayer));
    WindowGeometry  geo = (*(this->_currentLayer))->getGeometry();
    this->_view.setGeometry(geo._x, geo._y, geo._width,geo._height);
    this->_view.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->_view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_view.setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
    this->_view.show();

//     std::list<IAction*>	actList;

//     actList.push_back(new MoveAction(Qt::Key_Up));
//     actList.push_back(new MoveAction(Qt::Key_Left));
//     actList.push_back(new MoveAction(Qt::Key_Up));
//     actList.push_back(new MoveAction(Qt::Key_Left));

//     for (std::list<IAction*>::iterator
// 	   it = actList.begin(),
// 	   end = actList.end();
// 	 it != end; ++it)
//       {
// 	this->actionHandler(**it);
// 	//::sleep(2);
// 	delete *it;
//       }
}

void LayerManager::createLayers(std::list<Ceg::Window> & windows)
{
    std::list<Ceg::Window>::iterator it = windows.begin();
    std::list<Ceg::Window>::iterator itEnd = windows.end();

    for (; it != itEnd; ++it)
    {
	Layer * oneLayer = new Layer(*it);
	std::list<QGraphicsRectItem *> graphicItems;
	this->_boxManager->getPattern("Desktop", *it, graphicItems);
	oneLayer->initScene(graphicItems);
	this->_layers.push_front(oneLayer);
    }
}

bool    LayerManager::actionHandler(IAction & anAction)
{
    return (anAction.exec(*this));
}

AbstractScene*	LayerManager::getCurrentLayer() const
{
    return (*this->_currentLayer);
}

ICommunicationGraphicalServer*	LayerManager::getComGs() const
{
    return (this->_comGs);
}

BoxManager *	LayerManager::getBoxManager() const
{
    return (this->_boxManager);
}


View*	LayerManager::getView()
{
  return (&this->_view);
}
