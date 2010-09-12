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
#include <QTextStream>
/*********************************/
#include "ActionFactory.h"
/*********************************/
#include "Logger.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

QMap<QString, ActionFactory::ActionInstantiator> ActionFactory::_instanciators;

IAction *	ActionFactory::create(QDomElement const & actionElement)
{
    QString const & id = actionElement.attribute("id");
    QString msg;
    QTextStream tmp(&msg);
    tmp << "Demande d' instance de type: " << id;
    Logger::getInstance()->log(INFO_LOG, msg);

    QMap<QString, ActionInstantiator>::const_iterator itFind = ActionFactory::_instanciators.find(id);
    return (itFind != ActionFactory::_instanciators.end() ? (itFind.value())(actionElement) : 0);
}

/************************************************* [ OTHERS ] *************************************************/

void ActionFactory::registerInstantiator(const QString & actionId, ActionInstantiator function)
{
    QString msg;
    QTextStream tmp(&msg);
    tmp << "Action enregistree: " << actionId << "Valeur du pointeur : " << &function;
    Logger::getInstance()->log(INFO_LOG, msg);
    ActionFactory::_instanciators.insert(actionId, function);
}
