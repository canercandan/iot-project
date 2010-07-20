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
#include <iostream>
#include <climits>
#include <cstdio> /* pour le debug seulement */
#include <cstring> /* used for memset in generateEventClick */
/*********************************/
#include <QRect>
#include <QString>
#include <QVariant>
/*********************************/
#include "XWindowSystem.h"
/*********************************/
#include "Logger.h"
#include "Utils.h"

/* http://tronche.com/gui/x/xlib/ICC/client-to-window-manager/XGetTransientForHint.html
 * // confirm window is a client window
    Window client = XmuClientWindow (displ
 * http://stackoverflow.com/questions/736345/handle-new-top-level-window-events-in-xlib-xt
 *
Top level window on X Window System
Hello,

i want to print on the screen the informations about Top level windows under Linux.

I use the xlib functions. I successfully recurse from the root window to print all the informations about all the element on display.

But i need only the Top-Level window. I don't find any good way to filter.

From wikipedia :

> The top-level windows are exactly the
> direct subwindows of the root window.

With that definition , I have some windows like: gnome-session, seahorse-daemon,notify-osd or icons, on my list and i don't want them.

I also find a function : XmuClientWindow, but i don't understand it's goal.

Thanks to help me.*/

XWindowSystem::XWindowSystem() :
_connection(::XOpenDisplay(0))
{
}

XWindowSystem::~XWindowSystem()
{
    if (this->_connection != 0)
    {
	if (::XCloseDisplay(this->_connection) == BadGC)
	{
            Logger::getInstance()->Log(ERROR, "Scope : XWindowSystem::~XWindowSystem\tFunction : XCloseDisplay fail");
	}
	else
	{
            Logger::getInstance()->Log(ERROR,  "Connection to Graphical Server close with success.");
	}
    }
}

bool XWindowSystem::getWindows(std::list<Ceg::Window> &)
{
    if (this->_connection != 0)
    {
	::Window rootWindow = ::XDefaultRootWindow(this->_connection);
	this->printRecurse(rootWindow, 0);
    }
    return (this->_connection);
}

bool XWindowSystem::getFocusedWindow(Ceg::Window & /*newWindow*/)
{
    bool statusOp = false;
    if (this->_connection != 0)
    {
	::Window focusWindow;
	int focusState;
	int status = ::XGetInputFocus(this->_connection, &focusWindow, &focusState);
	if (status != BadValue && status != BadWindow && focusWindow != None)
	{
        //            QString msg("window Id: ");
        //            QVariant fwin(focusWindow);
        //            QVariant fstate(focusState);
        //            msg += fwin.toString(); msg += " focus state:";
        //            msg += fstate;
        //            Logger::getInstance()->Log(INFO, msg);
        //            newWindow.setId(focusWindow);
        //            statusOp = this->refreshWindowInfo(newWindow);
	    this->printWindow(focusWindow, 0);
	}
    }
    return (statusOp);
}

bool XWindowSystem::setFocusToWindow(Ceg::Window & , Ceg::Window & /*newFocusWindow*/)
{
    bool statusOp = false;
    if (this->_connection != 0)
    {
    //int status = ::XSetInputFocus(this->_connection, newFocusWindow, revert_to, time);
    }
    return (statusOp);
}

bool XWindowSystem::refreshWindowInfo(Ceg::Window & targetWindow)
{
    bool statusOp = false;
    if (this->_connection != 0)
    {
	::XWindowAttributes windowInfos;
	Status status = ::XGetWindowAttributes(this->_connection, targetWindow.getId(), &windowInfos);
	if (status != BadDrawable && status != BadWindow)
	{
	    targetWindow.setGeometry(QRect(windowInfos.x, windowInfos.y, windowInfos.width, windowInfos.height));
	    statusOp = true;
	}
    }
    return (statusOp);
}

void XWindowSystem::queryPointer(XEvent& event, Window& window, Window& subwindow)
{
  ::XQueryPointer(this->_connection, window,
		  &event.xbutton.root,
		  &subwindow,
		  &event.xbutton.x_root,
		  &event.xbutton.y_root,
		  &event.xbutton.x,
		  &event.xbutton.y,
		  &event.xbutton.state);
}

bool XWindowSystem::generateClickEvent(short int buttonID)
{
  /* juste pour info il existe l'outil xdotool qui permet entre autre de generer des touches claviers et deplacer la souris tres facilement voir http://www.semicomplete.com/projects/xdotool/ */

  /* set position avec QT */

  Display* display = this->_connection;

  if (display == 0)
    return (false);

  XEvent event;

  ::memset(&event, 0x0, sizeof(event));

  event.type = ButtonPress;
  event.xbutton.button = buttonID;
  event.xbutton.same_screen = True;

  this->queryPointer(event,
		     RootWindow(display, DefaultScreen(display)),
		     event.xbutton.window);

  event.xbutton.subwindow = event.xbutton.window;

  while (event.xbutton.subwindow)
    {
      event.xbutton.window = event.xbutton.subwindow;
      this->queryPointer(event,
			 event.xbutton.window,
			 event.xbutton.subwindow);
    }

  if (::XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)
    return (false);

  ::XFlush(display);

  ::usleep(100000);

  event.type = ButtonRelease;
  event.xbutton.state = 0x100;

  if (::XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)
    return (false);

  ::XFlush(display);

  return (true);
}

void XWindowSystem::printRecurse(::Window currentWindow, unsigned int level) const
{
    ::Window rootReturn, parentReturn;
    ::Window * childrenReturn = 0;
    unsigned int nbChildrenReturn = 0;
    Status status = XQueryTree(this->_connection, currentWindow, &rootReturn, &parentReturn, &childrenReturn, &nbChildrenReturn);
    if (status != BadWindow)
    {
        QString msg("Window ID : ");
        QVariant lvl(this->printIndent(level));
        //QVariant rootRet(&rootReturn);
        //msg += currentWindow; msg += " Root:"; msg += rootRet.toString();
        Logger::getInstance()->Log(INFO, msg);
        //lvl << "Parent : 0x" << std::hex << parentReturn << std::dec;
	pid_t pid = this->getPid(currentWindow);
        //	qDebug() << lvl << "Pid of the window's creator : " << pid;
        Logger::getInstance()->Log(INFO, msg);
	if (pid != 0)
	{
        //	  qDebug() << this->printIndent(level) << "Binaire utilise : " << this->getPathOfBinary(typeToString(pid)).c_str();
        Logger::getInstance()->Log(INFO, msg);
	}
	this->printCommands(currentWindow, level);
	this->printWindow(currentWindow, level);
        //	qDebug() << this->printIndent(level) << "Nb child : " << nbChildrenReturn;
        Logger::getInstance()->Log(INFO, msg);
	::Window muclient = ::XmuClientWindow(this->_connection, currentWindow);
        //	qDebug() << this->printIndent(level) << "XmuClientWindow : 0x" << muclient << "\n" <<
        msg = lvl.toString();
        Logger::getInstance()->Log(INFO, msg);
	for (unsigned int i = 0; i < nbChildrenReturn; ++i)
	{
	    this->printRecurse(childrenReturn[i], level + 1);
	}
	::XFree(childrenReturn);
    }
    else
    {
        Logger::getInstance()->Log(ERROR, "Scope : XWindowSystem::printRecurse\tFunction XQueryTree fail");
    }
}

pid_t XWindowSystem::getPid(::Window windowId) const
{
    // Un atom est un identifiant unique pour une propriete. d'une fenetre doc http://tronche.com/gui/x/xlib/window-information/properties-and-atoms.html
    Atom atomPid = ::XInternAtom(this->_connection, "_NET_WM_PID", True);
    pid_t pid = 0;
    if (atomPid != BadAlloc && atomPid != BadValue && atomPid != None)
    {
	Atom type;
	int format;
	unsigned long nItems;
	unsigned long bytesAfter;
	unsigned char *propPID = 0;
	if (::XGetWindowProperty(this->_connection, windowId, atomPid, 0, 1, False, XA_CARDINAL, &type, &format, &nItems, &bytesAfter, &propPID) == Success)
	{
	    if (propPID != 0)
	    {
		pid = *((pid_t *) propPID);
		::XFree(propPID);
	    }
	}
    }
    return (pid);
}

//redhat /exe
std::string XWindowSystem::getPathOfBinary(std::string const & pidStr) const
{
    std::string symbolicLink("/proc/" + pidStr + "/exe");
    char buffer[PATH_MAX];
    ssize_t size = readlink(symbolicLink.c_str(), buffer, PATH_MAX);
    if (size == -1)
    {
	perror("readlink : ");
    }
    else
    {
	buffer[size] = '\0';
	return (buffer);
    }
    return ("");
}

char XWindowSystem::printIndent(unsigned int nbIndent) const
{
    if (nbIndent > 0)
	for (unsigned int i = 0; i < (nbIndent - 1); ++i)
            Logger::getInstance()->Log(INFO, "*");
    return (' ');
}

void XWindowSystem::printWindow(::Window windowId, unsigned int level) const
{
    QString msg;
    XTextProperty propWindowName;
    if (::XGetWMName(this->_connection, windowId, &propWindowName) != 0)
    {
        QVariant lvl(this->printIndent(level));
        msg = lvl.toString(); msg += "Window Name : ";
        //QString value(propWindowName.value);
        //msg += value;
        Logger::getInstance()->Log(INFO, msg);
	::XFree(propWindowName.value);
    }
    else
    {
        Logger::getInstance()->Log(ERROR, "Scope : XWindowSystem::printWindow\tFunction XGetWMName fail");
    }

    XTextProperty propIconName;
    if (::XGetWMIconName(this->_connection, windowId, &propIconName) != 0)
    {
	if (propIconName.value != 0)
	{
            //qDebug() << this->printIndent(level) << "Icon Name : " << propIconName.value;
	    ::XFree(propIconName.value);
	}
    }

    XClassHint classHintsReturn;
    Status status = ::XGetClassHint(this->_connection, windowId, &classHintsReturn);
    if (status != 0 && status != BadWindow)
    {
	if (classHintsReturn.res_name)
	{
            //qDebug() << this->printIndent(level) << "Application Name : " << classHintsReturn.res_name;
	    ::XFree(classHintsReturn.res_name);
	}
	if (classHintsReturn.res_class)
	{
            //qDebug() << this->printIndent(level) << "Application Class : " << classHintsReturn.res_class;
	    ::XFree(classHintsReturn.res_class);
	}
    }
    else
    {
        Logger::getInstance()->Log(ERROR, "Scope : XWindowSystem::printWindow\tFunction XGetClassHint fail");
    }

    ::XWindowAttributes windowInfos;
    status = ::XGetWindowAttributes(this->_connection, windowId, &windowInfos);
    if (status != BadDrawable && status != BadWindow)
    {
        QString msg;
        QVariant varX, varY, varW, varH, varLevel;

        varLevel = this->printIndent(level);
        varX = windowInfos.x;
        varY = windowInfos.y;
        varW = windowInfos.width;
        varH = windowInfos.height;

        msg = varLevel.toString(); msg += "x : "; msg += varX.toString();
        Logger::getInstance()->Log(INFO, msg);
        msg = varLevel.toString(); msg += "Y : ";msg += varY.toString();
        Logger::getInstance()->Log(INFO, msg);
        // cf function Display_Stats_Info for absolute window
        msg = varLevel.toString(); msg += "heigth : ";msg += varH.toString();
        Logger::getInstance()->Log(INFO, msg);
        msg = varLevel.toString(); msg += "width : ";msg += varW.toString();
        Logger::getInstance()->Log(INFO, msg);
        msg = varLevel.toString(); msg += "Visible :"; msg += ((windowInfos.map_state == IsUnmapped) ? "IsUnmapped" : (windowInfos.map_state == IsUnviewable) ? "IsUnviewable" : "IsViewable");
        Logger::getInstance()->Log(INFO, msg);
    }
    else
    {
        Logger::getInstance()->Log(ERROR, "Scope : XWindowSystem::printWindow\tFunction XGetWindowAttributes fail");
    }
}

void XWindowSystem::printCommands(::Window windowId, unsigned int /*level*/) const
{
    int argcReturn;
    char **argvReturn;
    Status status = ::XGetCommand(this->_connection, windowId, &argvReturn, &argcReturn);
    if (status != 0)
    {
        //qDebug() << this->printIndent(level) << "argc : " << argcReturn;
        //qDebug() << this->printIndent(level) << "argv :";
	for (int i = 0; i < argcReturn; ++i)
	{
            //qDebug() << ' ' << argvReturn[i];
	}
        //qDebug();
	::XFreeStringList(argvReturn);
    }
    else
    {
        Logger::getInstance()->Log(ERROR, "Scope : XWindowSystem::printCommands\tFunction XGetCommand fail");
    }
}
