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


#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include <string>
#include <map>

class QDomElement;
class IAction;

/*
  Pattern Factory
  Permet de creer une Action selon son Id
  */
class ActionFactory
{
public:
    typedef IAction * (*ActionInstantiator)(QDomElement const &);

    static IAction *	create(QDomElement const & domElement); // Retourne l'action demande
    static void		registerInstantiator(std::string const & actionId, ActionInstantiator function); // Permet de referencer une action et son constructeur
    static void		printRegisterInstantiator();

private:
    static std::map<std::string, ActionInstantiator>	_instanciators; // Reference les ids des actions et leur constructeurs associes
};

#endif // ACTIONFACTORY_H
