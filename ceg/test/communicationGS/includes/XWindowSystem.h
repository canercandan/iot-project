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

#ifndef XWINDOWSYSTEM_H_
#define XWINDOWSYSTEM_H_

#include "ICommunicationGraphicalServer.h"

/* doc pour l'API http://tronche.com/gui/x/xlib/
 * ressource tres utile http://standards.freedesktop.org/wm-spec/1.3/ar01s05.html
 * pour recupere le PID du programme http://lists.samba.org/archive/linux/2008-July/020298.html  _NET_WM_PID
 * http://stackoverflow.com/questions/151407/how-to-get-an-x11-window-from-a-process-id
 * avoir la derniere fenetre qui poppe XGetInputFocus
 */

class XWindowSystem : public ICommunicationGraphicalServer
{
public:
    XWindowSystem();
    ~XWindowSystem();

    virtual bool getWindows(std::list<Ceg::Window> &);
    virtual bool getFocusedWindow(Ceg::Window & focusedWindow);
    virtual bool setFocusToWindow(Ceg::Window & oldFocusedWindow, Ceg::Window & newFocusedWindow);
    virtual bool refreshWindowInfo(Ceg::Window &);
    virtual bool generateClickEvent(short int x, short int y);

private:
    char printIndent(unsigned int) const;
    void printCommands(::Window, unsigned int) const;
    void printWindow(::Window, unsigned int) const;
    void printRecurse(::Window, unsigned int level) const;
    pid_t getPid(::Window) const;
    std::string getPathOfBinary(std::string const & pidStr) const;

private:
    ::Display* _connection;
};

#endif // XWINDOWSYSTEM_H_
