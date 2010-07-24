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
#include <QDomNode>
#include <QDebug>
/*********************************/
#include "ExecMenuAction.h"
/*********************************/
#include "MainController.h"
#include "ActionFactory.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * ExecMenuAction::IDENTIFIER = "ExecMenu";

ExecMenuAction::ExecMenuAction(IAction * actionToExec)
{
   this->_actionsToExec.push_back(actionToExec);
}

ExecMenuAction::ExecMenuAction(const QDomElement & domElement)
{
    this->initializeFromXml(domElement);
}

ExecMenuAction::~ExecMenuAction()
{
    for (std::vector< IAction * >::iterator
	 it = _actionsToExec.begin(),
	 end = _actionsToExec.end();
    it != end; ++it)
    {
	delete *it;
    }
}

void ExecMenuAction::initializeFromXml(const QDomElement & actionElement)
{
    for (QDomNode domElement = actionElement.firstChild(); !domElement.isNull(); domElement = domElement.nextSibling())
    {
	QDomElement const & actionParam = domElement.toElement();
	if (actionParam.isNull() == false && actionParam.tagName() == "action")
	{
	    qDebug() << "action added";
	    IAction * anAction = ActionFactory::create(actionParam);
	    if (anAction != 0)
		this->_actionsToExec.push_back(anAction);
	}
    }
}

/************************************************* [ OTHERS ] *************************************************/

void ExecMenuAction::exec(MainController & mainC)
{
    qDebug() << "ExecMenuAction::exec";
    if (this->_actionsToExec.empty() == false)
    {
	// On execute l'action
	for (std::vector< IAction * >::iterator it = this->_actionsToExec.begin(), end = this->_actionsToExec.end(); it != end; ++it)
	{
	    (*it)->exec(mainC);
	}
    }
    else
    {
	qDebug() << "Action null, rien a executer";
    }
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateExecMenuAction(QDomElement const & actionElement)
{
    return (new ExecMenuAction(actionElement));
}
