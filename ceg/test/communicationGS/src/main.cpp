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

#include <iostream>
#include <cstdlib>

#ifdef _WIN32

#include "Win32Explorer.h"

int main(int argc, char *argv[], char *envp[])
{
    ICommunicationGraphicalServer * comGS = new Win32Explorer();
    std::list<Ceg::Window> windows;
    std::cout << "Top Level Windows: " << std::endl;
    comGS->getWindows(windows);
    Ceg::Window temp;
    comGS->getFocusedWindow(temp);

    delete comGS;
    return (EXIT_SUCCESS);
}

#else

#include "XWindowSystem.h"


int main()
{
    ICommunicationGraphicalServer * comGS = new XWindowSystem();
    std::list<Ceg::Window> windows;
    std::cout << "Top Level Windows: " << std::endl;
    comGS->getWindows(windows);
//    Ceg::Window temp;
//    comGS->getFocusedWindow(temp);342946d

    delete comGS;
    return (EXIT_SUCCESS);
}

#endif
