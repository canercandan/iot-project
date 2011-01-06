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
#include "MainController.h"
/*********************************/
#include "Layer.h" // debug
#include "Window.h" // debug
#include "BoxController.h"
#include "IAction.h"
#include "Utils.h"
#include "WindowSystem.h"
#include "PopMenuAction.h"
#include "Logger.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

MainController::MainController(Systray & systray) :
        _view(*this, systray), _scenes(), _boxController(),
	_comGs(new WindowSystem), _tcpServer(*this)
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
    return (this->_scenes.front());
}

AbstractScene * MainController::getScene(const QString &id) const
{
    for (QList<AbstractScene *>::const_iterator it = this->_scenes.begin(), itEnd = this->_scenes.end(); it != itEnd; ++it)
    {
        if (**it == id)
        {
            return (*it);
        }
    }
    return (0);
}

int MainController::getIndexOfScene(AbstractScene * sceneSearch) const
{
    return (this->_scenes.indexOf(sceneSearch));
}

int MainController::getFirstOfType(BoxType type) const
{
    int i = 0;
    for (QList<AbstractScene *>::const_iterator it = this->_scenes.begin(), itEnd = this->_scenes.end(); it != itEnd; ++it, ++i)
    {
        if (**it == type)
        {
            return (i);
        }
    }
    return (-1);
}

AbstractScene * MainController::getSceneAt(int position) const
{
    if (position < this->_scenes.size())
    {
        return (this->_scenes.at(--position));
    }
    return (0);
}

AbstractScene * MainController::getFirstNavigationScene() const
{
    for (QList<AbstractScene *>::const_iterator it = this->_scenes.begin(), itEnd = this->_scenes.end(); it != itEnd; ++it)
    {
        if (**it == DEFAULT_BOX || **it == CUSTOM_BOX)
        {
            return (*it);
        }
    }
    return (0);
}

View &	MainController::getView()
{
    return (this->_view);
}

Ceg::Window & MainController::getWindow()
{
    return this->_ownWindow;
}

/************************************************* [ OTHERS ] *************************************************/

void    MainController::on_action_emitted(IAction & anAction)
{
    anAction.exec(*this);
}

AbstractScene * MainController::createScene(Ceg::Window const & window)
{
    Layer * oneLayer = new Layer(window, *this);
    QList<QGraphicsRectItem *> graphicItems;
    this->_boxController.getPattern(window, graphicItems);
    oneLayer->initialize(graphicItems);
    return (oneLayer);
}

void MainController::initialize()
{
    Logger::getInstance()->log(INFO_LOG, "Initialisation du MainController.");
    PopMenuAction popAction("Home");
    this->on_action_emitted(popAction);
}


void MainController::on_start_navigation()
{
    Logger::getInstance()->log(INFO_LOG,"Demarrage de la navigation.");
    static bool isInit = false;
    if (isInit == false || this->_scenes.empty() == true) // si c la premiere fois que l on lance la navigation ou qu'il n'y a plus de scene en cours d'utilisation
    {
	this->initialize();
	this->_view.initialize();
	isInit = true;
    }
    this->_view.show();
    this->_comGs->getFocusedWindow(this->_ownWindow);
}

void MainController::on_stop_navigation()
{
    Logger::getInstance()->log(INFO_LOG,"Stoppage de la navigation.");
    this->_view.hide();
}

void MainController::pushFrontScene(AbstractScene *scene)
{
    this->_scenes.removeOne(scene); // Lorsqu'on effectue un zoom, cela evite d'avoir a deplacer la scene, on remove et au insert au depart
    this->_scenes.push_front(scene);
    this->_view.setScene(this->_scenes.front());
    this->_view.setSceneRect(this->_scenes.front()->getGeometry());
}

void MainController::popFrontScene()
{
    AbstractScene const * oldCurrentScene = this->_scenes.front();
    this->_scenes.pop_front();
    if (this->_scenes.empty() == false)
    {
        this->_view.setScene(this->_scenes.front());
        this->_view.setSceneRect(this->_scenes.front()->getGeometry());
    }
    delete oldCurrentScene;
}

void MainController::removeSceneAt(int index)
{
    AbstractScene const * deletedScene = this->_scenes.at(index);
    this->_scenes.removeAt(index);
    delete deletedScene;
    this->pushFrontScene(this->getScene("Home"));
}
