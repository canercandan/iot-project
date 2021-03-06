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

#ifndef WINDOW_H_
#define WINDOW_H_

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>		// NT only!
#pragma comment(lib, "psapi")	// NT only!
#else
#include <X11/Xlib.h>
#endif
#include "WindowGeometry.h"

namespace Ceg
{
#ifdef _WIN32
    typedef ::HWND WindowId;
#else
    typedef ::Window WindowId;
#endif

    class Window
    {
    public:
        Window();
        Window(WindowId, WindowGeometry const &, bool = false);

        WindowId getId() const;
        void setId(WindowId);
        void setCharacteristic(WindowGeometry const &);

    private:
        WindowId _id;
        WindowGeometry _characteristic;
        bool _isVisible;
    };
}

#endif // WINDOW_H_
