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

#if defined(__MINGW32__)

#include "ICommunicationGraphicalServer.h"

class WindowSystem : public ICommunicationGraphicalServer
{
public:
    WindowSystem()
    {}

    virtual inline bool getWindows(std::list<Ceg::Window> & windows)
    {return true;}

    virtual inline bool getFocusedWindow(Ceg::Window & focusedWindow)
    {return true;}

    virtual inline bool setFocusToWindow(Ceg::Window & oldFocusedWindow, Ceg::Window & newFocusedWindow)
    {return true;}

    virtual inline bool refreshWindowInfo(Ceg::Window &)
    {return true;}

    virtual inline bool generateClickEvent(short int buttonID)
    {return true;}
};

#elif defined(Q_WS_WIN)

//#warning "WINDOWS"

#include "Win32Explorer.h"

typedef Win32Explorer	WindowSystem;

#elif defined(Q_WS_X11) || defined(Q_WS_MAC)

#include "XWindowSystem.h"

typedef XWindowSystem	WindowSystem;

#else

//#warning "Not yet implemented"

#endif
