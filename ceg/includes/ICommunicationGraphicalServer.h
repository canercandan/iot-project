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

#ifndef ICOMMUNICATIONGRAPHICALSERVER_H_
#define ICOMMUNICATIONGRAPHICALSERVER_H_

#include <list>

#include "Window.h"

/**
 * \interface ICommunicationGraphicalServer
 * \brief Interface permettant la communication avec le serveur graphique
 */
 
 /* 
 * Cette interface doit etre implemente pour tout les serveurs graphiques existants.
 * Elle permet la communication avec le serveur graphique pour recuperer des informations sur les fenetres ou sur-generer des evenements souris.
 */

class ICommunicationGraphicalServer {
public:

    /**
     * \brief Destructeur
     */
    virtual ~ICommunicationGraphicalServer() {
    }

    /**
     * \brief Permet de recuperer la liste de toutes les fenetres affichees a l'ecran.
     * \param windows [out] la liste de toutes les fenetres affichees a l'ecran, cette liste est vide a l'entree.
     * \return Vrai en cas de succes, faux en cas d'erreur
     */
    virtual bool getWindows(std::list<Ceg::Window> & windows) = 0;

    /**
     * \brief Permet de recuperer la fenetre possedant le focus
     * \param windows [out] la liste de toutes les fenetres affichees a l'ecran, cette liste est vide a l'entree.
     * \return Vrai en cas de succes, faux en cas d'erreur
     */

    virtual bool getFocusedWindow(Ceg::Window & focusedWindow) = 0;

    virtual bool setFocusToWindow(Ceg::Window & oldFocusedWindow, Ceg::Window & newFocusedWindow) = 0;

    virtual bool refreshWindowInfo(Ceg::Window &) = 0;

    virtual bool generateClickEvent(short int buttonID) = 0;
};

#endif // ICOMMUNICATIONGRAPHICALSERVER_H_
