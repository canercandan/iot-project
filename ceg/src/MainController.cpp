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
#include <QDebug>
/*********************************/
#include "MainController.h"
/*********************************/
#include "Layer.h" // debug
#include "Window.h" // debug
#include "BoxController.h"
#include "IAction.h"
#include "Utils.h"
#include "WindowSystem.h"
#include "PopMenuAction.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

MainController::MainController(Systray & systray) :
	_view(*this, systray), _scenes(),_currentScene(), _boxController(),
	_comGs(new WindowSystem), _tcpServer(*this)

#ifndef Q_WS_WIN
	, _logger(log4cxx::Logger::getLogger("ceg.main"))
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


AbstractScene *	MainController::getCurrentScene() const
{
    return (*this->_currentScene);
}

View &	MainController::getView()
{
    return (this->_view);
}

/************************************************* [ OTHERS ] *************************************************/

void    MainController::on_action_emitted(IAction & anAction)
{
#ifndef Q_WS_WIN
    LOG4CXX_INFO (this->_logger, "Execution de l'action suivante : .");
#endif
    anAction.exec(*this);
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
#ifndef Q_WS_WIN
    LOG4CXX_INFO (this->_logger, "Initialisation.");
#endif

    PopMenuAction popAction("Home");
    this->on_action_emitted(popAction);
}


void MainController::on_start_navigation()
{
#ifndef Q_WS_WIN
    LOG4CXX_INFO (this->_logger, "Demarrage de la navigation.");
#endif
    static bool isInit = false;
    if (isInit == false)
    {
	this->initialize();
	this->_view.initialize();
	isInit = true;
    }
    this->_view.show();
}

void MainController::on_stop_navigation()
{
#ifndef Q_WS_WIN
    LOG4CXX_INFO (this->_logger, "Stoppage de la navigation.");
#endif

    this->_view.hide();
}

void MainController::pushFrontScene(AbstractScene *scene)
{
    this->_scenes.push_front(scene);
    this->_currentScene = this->_scenes.begin();
    this->_view.hide();
    this->_view.setScene(*(this->_currentScene));
    this->_view.show();
}

void MainController::popFrontScene()
{
    AbstractScene const * currentScene = *(this->_currentScene);
    this->_scenes.pop_front();
    this->_currentScene = this->_scenes.begin();
    this->_view.hide();
    this->_view.setScene(*(this->_currentScene));
    this->_view.setGeometry((*this->_currentScene)->getGeometry());
    this->_view.show();
    delete currentScene;
}
