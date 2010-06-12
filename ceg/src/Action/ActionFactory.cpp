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
#include <QDebug>
/*********************************/
#include "ActionFactory.h"
/*********************************/

std::map<std::string, ActionFactory::ActionInstantiator> ActionFactory::_instanciators;

IAction *	ActionFactory::create(std::string const & actionId, QDomElement const & actionElelement)
{
    std::map<std::string, ActionInstantiator>::const_iterator itFind = ActionFactory::_instanciators.find(actionId);
    return (itFind != ActionFactory::_instanciators.end() ? (itFind->second)(actionElelement) : 0);
}

void ActionFactory::registerInstantiator(const std::string &actionId, ActionInstantiator function)
{
    ActionFactory::_instanciators.insert(std::make_pair(actionId, function));
}

void ActionFactory::printRegisterInstantiator()
{
    qDebug() << "Actions Registers : " << ActionFactory::_instanciators.size();
    for (std::map<std::string, ActionInstantiator>::const_iterator it = ActionFactory::_instanciators.begin(),
	 itEnd = ActionFactory::_instanciators.end(); it != itEnd; ++it)
    {
	qDebug() << "Id = " << (it->first).c_str();
    }
}
