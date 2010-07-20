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
#include <QDomElement>
#include <QProcess>
/*********************************/
#include "ExecProcessAction.h"
/*********************************/
#include "MainController.h"
#include "Utils.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * ExecProcessAction::IDENTIFIER = "ExecProcess";

ExecProcessAction::ExecProcessAction(const QDomElement & actionElement) : _path(""), _hideTime(1000)
{
    qDebug() << "ExecProcessAction::ExecProcessAction(const QDomElement & actionElement)";
    this->initializeFromXml(actionElement);
}

void ExecProcessAction::initializeFromXml(const QDomElement & domElement)
{
    if (domElement.hasAttribute("time"))
	{
	    this->_hideTime = domElement.attribute("time").toULong();
	}

#if defined(Q_OS_UNIX)
    if (domElement.hasAttribute("unix:path"))
	{
	    //this->_path = domElement.attribute("path");
	    this->_path = domElement.attribute("unix:path");
	}
#elif defined(Q_OS_WIN)
    if (domElement.hasAttribute("win:path"))
	{
	    //this->_path = domElement.attribute("path");
	    this->_path = domElement.attribute("unix:path");
	}
#elif defined(Q_OS_MAC)
    if (domElement.hasAttribute("mac:path"))
	{
	    //this->_path = domElement.attribute("path");
	    this->_path = domElement.attribute("mac:path");
	}
#endif
    else if (domElement.hasAttribute("path"))
	{
	    this->_path = domElement.attribute("path");
	}
}

/************************************************* [ OTHERS ] *************************************************/

void	ExecProcessAction::exec(MainController & lm)
{
    qDebug() << "ExecProcessAction::exec";

    if (this->_path == "")
	{
	    qDebug() << "No path found";
	    return;
	}

    qDebug() << "We are going to execute" << this->_path;

    View & view = lm.getView();
    view.hide();

    QProcess* process = new QProcess( &lm );
    process->start( this->_path );

    SleeperThread::msleep(this->_hideTime);

    view.show();
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateExecProcessAction(const QDomElement & actionElement)
{
    return (new ExecProcessAction(actionElement));
}
