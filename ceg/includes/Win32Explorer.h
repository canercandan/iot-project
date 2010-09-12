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

#ifndef WIN32EXPLORER_H_

# define WIN32EXPLORER_H_

#include "ICommunicationGraphicalServer.h"


class Win32Explorer : public ICommunicationGraphicalServer
{
public:
    Win32Explorer();
    ~Win32Explorer();
    virtual bool	getFocusedWindow(Ceg::Window &);
    virtual bool	setFocusToWindow(Ceg::Window & oldFocusedWindow, Ceg::Window & newFocusedWindow);
    virtual bool	generateClickEvent(short int buttonID);
    virtual bool	generateKeybdEvent(unsigned char key);
};


#endif //! WIN32EXPLORER_H_
