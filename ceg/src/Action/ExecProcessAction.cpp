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
#include <QProcess>
#include <QApplication>
#include <QDesktopWidget>
#include <QTextStream>
#include <QFileInfo>
/*********************************/
#include "ExecProcessAction.h"
/*********************************/
#include "MainController.h"
#include "Window.h"
#include "Layer.h"
#include "Utils.h"
#include "Logger.h"
/*********************************/

#if defined(Q_OS_UNIX)
static const QString osName("unix");
#elif defined(Q_OS_WIN)
static const QString osName("win");
#elif defined(Q_OS_MAC)
static const QString osName("mac");
#endif

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * ExecProcessAction::IDENTIFIER = "ExecProcess";

ExecProcessAction::ExecProcessAction(const QDomElement & actionElement) : _path(""), _pathFinder(""), _arguments(""), _hideTime(2000)
{
    Logger::getInstance()->log(DEBUG_LOG, "ExecProcessAction::ExecProcessAction(const QDomElement & actionElement)");
    this->initializeFromXml(actionElement);
}

void ExecProcessAction::initializeFromXml(const QDomElement & domElement)
{
    if (domElement.hasAttribute("time"))
    {
	this->_hideTime = domElement.attribute("time").toULong();
    }

    if (domElement.hasAttribute(osName + ":path"))
    {
        this->_path = domElement.attribute(osName + ":path");
    }

    if (domElement.hasAttribute((osName + ":pathfinder")))
    {
        this->_pathFinder = domElement.attribute(osName + ":pathfinder");
    }

    if (domElement.hasAttribute(osName + ":arguments"))
    {
        this->_arguments = domElement.attribute(osName + ":arguments");
    }

    if (this->_path.isEmpty() && domElement.hasAttribute("path"))
    {
	this->_path = domElement.attribute("path");
    }

    if (this->_pathFinder.isEmpty() && domElement.hasAttribute("pathfinder"))
    {
	this->_pathFinder = domElement.attribute("pathfinder");
    }

    if (this->_arguments.isEmpty() && domElement.hasAttribute("arguments"))
    {
	this->_arguments = domElement.attribute("arguments");
    }

#if defined(Q_OS_WIN)

    if (!this->_path.isEmpty())
    {
	this->_path = "\"" + this->_path + "\"";
    }

    if (!this->_pathFinder.isEmpty())
    {
	this->_pathFinder = "\"" + this->_pathFinder + "\"";
    }

    if (!this->_arguments.isEmpty())
    {
	this->_arguments = "\"" + this->_arguments + "\"";
    }

#endif
}

/************************************************* [ OTHERS ] *************************************************/

void	ExecProcessAction::exec(MainController & mainC)
{
    QString msg;
    QTextStream tmp(&msg);

    Logger::getInstance()->log(DEBUG_LOG, "ExecProcessAction::exec");

    if (!this->_pathFinder.isEmpty())
    {
	QProcess finder;
        finder.start(this->_pathFinder);

        if (!finder.waitForStarted())
	{
            Logger::getInstance()->log(DEBUG_LOG, "Finder command doesnot work.");
	    return;
	}

        if (! finder.waitForFinished())
	{
            Logger::getInstance()->log(DEBUG_LOG, "Finder command meets some issues to finish.");
	    return;
	}

	QString path = finder.readAll();
	path = path.trimmed();

#if defined(Q_OS_UNIX)
	path = path.split(" ")[0];
#endif

	if ( ! path.isEmpty() )
	{
	    this->_path = path;
	}
    }

    if (this->_path.isEmpty())
    {
        Logger::getInstance()->log(DEBUG_LOG, "No path found");
	return;
    }

    tmp << "We are going to execute" << this->_path;
    Logger::getInstance()->log(DEBUG_LOG, msg);

    QProcess* process = new QProcess(&mainC);
    process->start(this->_path + " " + this->_arguments);

    if (process->waitForStarted() == false)
    {
        Logger::getInstance()->log(DEBUG_LOG, "Program command doesn't work.");
	return;
    }

    if (this->_hideTime > 0)
    {
        SleeperThread::msleep(this->_hideTime);
    }
    QFileInfo   programFileInfo(this->_path);
    Ceg::Window defaultWindow(0, QApplication::desktop()->geometry(), programFileInfo.baseName());
    Layer * scene = static_cast<Layer *>(mainC.createScene(defaultWindow));
    /* Explication des conditions suivantes :
       Lorsqu'on est sur Linux, mac, quand on demarre un programme, notre fenetre reste au top mais perd le focus, de faire le hide and show permet de le conserver
       */
    View &  view = mainC.getView();
#if defined(Q_WS_X11) || defined(Q_WS_MAC)
    view.hide();
#endif
    mainC.pushFrontScene(scene);
    view.activateWindow();
#if defined(Q_WS_X11) || defined(Q_WS_MAC)
    view.show();
#endif
    scene->setProcess(process);
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateExecProcessAction(const QDomElement & actionElement)
{
    return (new ExecProcessAction(actionElement));
}
