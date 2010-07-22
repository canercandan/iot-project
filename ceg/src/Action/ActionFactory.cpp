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
#include <QDomElement>
#include <QVariant>
/*********************************/
#include "ActionFactory.h"
/*********************************/
#include "Logger.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

std::map<std::string, ActionFactory::ActionInstantiator> ActionFactory::_instanciators;

IAction *	ActionFactory::create(QDomElement const & actionElelement)
{
    std::string const & id = actionElelement.attribute("id").toStdString();
    QString msg("Demande d' instance de type ");
    msg += id.c_str();
    Logger::getInstance()->log(INFO_LOG, msg);

    std::map<std::string, ActionInstantiator>::const_iterator itFind = ActionFactory::_instanciators.find(id);
    return (itFind != ActionFactory::_instanciators.end() ? (itFind->second)(actionElelement) : 0);
}

/************************************************* [ OTHERS ] *************************************************/

void ActionFactory::registerInstantiator(const std::string &actionId, ActionInstantiator function)
{
    //FIX ME Afficher le pointeur
    QString msg("Action enregistree:");
    //QVariant funcaddr = (void *)function;
    msg += actionId.c_str(); msg += " Valeur du pointeur : ";
    Logger::getInstance()->log(INFO_LOG, msg);

  ActionFactory::_instanciators.insert(std::make_pair(actionId, function));
}
