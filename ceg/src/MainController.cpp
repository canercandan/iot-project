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
#include <algorithm>
/*********************************/
#include <QApplication>
#include <QDesktopWidget>
/*********************************/
#include "MainController.h"
/*********************************/
#include "Layer.h" // debug
#include "Window.h" // debug
#include "BoxController.h"
#include "IAction.h"
#include "Utils.h"
#ifdef _WIN32
#include "Win32Explorer.h"
#else
#include "XWindowSystem.h"
#endif
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

MainController::MainController() :
  _view(*this), _scenes(),_currentLayer(), _boxController(),
#ifdef _WIN32
	_comGs(new Win32Explorer)
#else
	_comGs(new XWindowSystem)
#endif
{
}

MainController::~MainController()
{
    std::for_each(this->_scenes.begin(), this->_scenes.end(), Ceg::DeleteObject());
    delete this->_comGs;
}

/************************************************* [ GETTERS ] *************************************************/

BoxController const &	MainController::getBoxController() const
{
    return (this->_boxController);
}

ICommunicationGraphicalServer *	MainController::getComGs() const
{
    return (this->_comGs);
}

AbstractScene*	MainController::getCurrentScene() const
{
    return (*this->_currentLayer);
}

View &	MainController::getView()
{
    return (this->_view);
}

/************************************************* [ OTHERS ] *************************************************/

bool    MainController::actionHandler(IAction & anAction)
{
    return (anAction.exec(*this));
}

void MainController::createScenes(std::list<Ceg::Window> const & windows)
{
    for (std::list<Ceg::Window>::const_iterator it = windows.begin(), itEnd = windows.end(); it != itEnd; ++it)
    {
	Layer * oneLayer = new Layer(*it);
	std::list<QGraphicsRectItem *> graphicItems;
	this->_boxController.getPattern(*it, graphicItems);
	oneLayer->initialize(graphicItems);
	this->_scenes.push_front(oneLayer);
    }
}

void MainController::initialize()
{
    std::list<Ceg::Window>  windows;
    //this->_comGs->getWindows(windows);

    QDesktopWidget *desktop = QApplication::desktop();
    windows.push_back(Ceg::Window(0, QRect(0 , 0, desktop->width(), desktop->height()), true, "Firefox"));

    this->createScenes(windows);
    this->_currentLayer = this->_scenes.begin();
}

void MainController::start()
{
    this->initialize();
    this->_view.initialize();
    this->_view.show();
}

void MainController::stop()
{
    this->_view.hide();
}
