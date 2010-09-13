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

#include <QRect>
#include <QString>

#if defined(__MINGW32__)
// do stuff...
#elif defined(Q_WS_WIN)
#include <windows.h>
#include <psapi.h>		// NT only!
//#pragma comment(lib, "psapi")	// NT only!
#elif defined(Q_WS_X11) || defined(Q_WS_MAC)
#include <X11/Xlib.h>
#endif

namespace Ceg
{
    typedef
#if defined(__MINGW32__)
            void*
#elif defined(Q_WS_WIN)
            ::HWND
#elif defined(Q_WS_X11) || defined(Q_WS_MAC)
            ::Window
#else
            void*
#endif

            WindowId;

    class Window
    {
    public:
	Window();
        Window(WindowId, QRect const &, QString const & = "");

	QRect const &	    getGeometry() const;
	WindowId	    getId() const;
        QString const &     getProgramName() const;

	void		    setGeometry(QRect const &);
	void		    setId(WindowId);

    private:
        QString _programName; // le nom du programme de la fenetre espionnee
	WindowId    _id;
	QRect	    _geometry; // La taille de la fenetre
    };
}

#endif // WINDOW_H_
