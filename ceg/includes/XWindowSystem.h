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

#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xmu/WinUtil.h>

#include "ICommunicationGraphicalServer.h"

/*
 * doc pour l'API http://tronche.com/gui/x/xlib/
 * ressource tres utile http://standards.freedesktop.org/wm-spec/1.3/ar01s05.html
 */

class XWindowSystem : public ICommunicationGraphicalServer
{
public:
    XWindowSystem();
    ~XWindowSystem();

    virtual bool    getFocusedWindow(Ceg::Window & focusedWindow);
    virtual bool    setFocusToWindow(Ceg::Window & oldFocusedWindow, Ceg::Window & newFocusedWindow);
    virtual bool    generateClickEvent(short int buttonID);
    virtual bool    generateKeybdEvent(quint32 key);

private:
    bool            generateClick(short int buttonID);
    char	    printIndent(unsigned int) const;
    void	    printWindow(::Window, unsigned int) const;
    void	    printRecurse(::Window, unsigned int level) const;
    void	    queryPointer(XEvent&, Window& window, Window& subwindow);

private:
    ::Display * _connection; // Connection avec le serveur graphique
};

#endif // XWINDOWSYSTEM_H_
