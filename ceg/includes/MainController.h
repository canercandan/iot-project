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

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <list>

#include <QGraphicsView>

#include "CegTcpServer.h"
#include "View.h"
#include "Window.h"
#include "BoxController.h"

class AbstractScene;
class ICommunicationGraphicalServer;
class IAction;
class Systray;

/**
 * \brief Classe de Controle
 * Elle Gere le fonctionnement general du CEG et ses evenements (actions | reseau)
 */
class MainController : public QObject
{
    Q_OBJECT
public:
    MainController(Systray &);
    ~MainController();

    BoxController const &		getBoxController() const;
    ICommunicationGraphicalServer*	getComGs() const;
    AbstractScene*			getCurrentScene() const; // Renvoie la scene qui est en premier dans la liste
    AbstractScene*			getSceneAt(size_t pos) const; // renvoie la scene a la pos
    View &				getView();

    AbstractScene *			createScene(Ceg::Window const & window);
    void				pushFrontScene(AbstractScene * scene); // Rajoute la scnene au debut des scenes et rafraichi la vue
    void				popFrontScene(); // Supprime la scene du debut et rafraichi la vue

public slots:
    void				on_start_navigation(); // Active la navigation
    void				on_stop_navigation(); // Stop la navigationF
    void				on_action_emitted(IAction &); // Attrape les actions a execute

private:
    void				initialize(); // Initialise tout les paremetres pour la navigation


private:
    View				    _view; // La vue pour representer les scene (Une vue pour toutes les scenes)
    std::list<AbstractScene *>		    _scenes; // L'ensemble des scenes, une scnene par fenetre systemes ouvertes + eventuellement un menu
    std::list<AbstractScene *>::iterator    _currentScene; // La scene utilise
    BoxController			    _boxController;
    ICommunicationGraphicalServer *	    _comGs;
    CegTcpServer                            _tcpServer;
};

#endif // MAINCONTROLLER_H
