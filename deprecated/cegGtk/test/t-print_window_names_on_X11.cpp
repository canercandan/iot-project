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

// http://tronche.com/gui/x/xlib/
// refer to LICENSE to xlsclient.c

#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xmu/WinUtil.h>

#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cassert>

#define MAXCMDLEN	10000
#define NIL		"(nil)"

// static void	lookat(Display *dpy, Window root);
// static void	print_client_properties(Display *dpy, Window w)
// static void	print_text_field(Display *dpy, char *s, XTextProperty *tp);
// static int	print_quoted_word(char *s, int maxlen);
// static void	unknown(Display *dpy, Atom actual_type, int actual_format);

// static void	lookat(Display* dpy, Window root)
// {
//   /*
//    * clients are not allowed to stomp on the root and ICCCM doesn't yet
//    * say anything about window managers putting stuff there; but, try
//    * anyway.
//    */
//   print_client_properties(dpy, root);

//   /*
//    * then, get the list of windows
//    */
//   Window	dummy;
//   Window*	children = NULL;
//   unsigned int	nchildren = 0;

//   if (!XQueryTree(dpy, root, &dummy, &dummy, &children, &nchildren))
//     return;

//   for (unsigned int i = 0; i < nchildren; ++i)
//     {
//       client = XmuClientWindow(dpy, children[i]);
//       if (client == None)
// 	continue;
//       print_client_properties(dpy, client);
//     }
// }

// static void	print_client_properties(Display* dpy, Window w)
// {
//   XTextProperty	machtp;

//   if (!XGetWMClientMachine(dpy, w, &machtp))
//     {
//       machtp.value = NULL;
//       machtp.encoding = None;
//     }

//   char**	cliargv = NULL;
//   int		cliargc;

//   if (!XGetCommand(dpy, client, &cliargv, &cliargc))
//     {
//       if (machtp.value)
// 	XFree((char*)machtp.value);
//       return;
//     }
// }

int	main(void)
{
  Display*	dpy = XOpenDisplay(NULL);

  assert(dpy);

  int	screenNumber = DefaultScreen(dpy);

  int	width = XDisplayWidth(dpy, screenNumber);
  int	height = XDisplayHeight(dpy, screenNumber);

  std::cout << "width:" << width << std::endl;
  std::cout << "height:" << height << std::endl;

  Window	top = XRootWindow(dpy, screenNumber);
  Window*	children;
  Window	dummy;
  unsigned int	nchildren;

  assert(XQueryTree(dpy, top, &dummy, &dummy, &children, &nchildren));

  for (unsigned int i = 0; i < nchildren; ++i)
    {
      Window	client;

      if ((client = XmuClientWindow(dpy, children[i])) == None)
	continue;

      XTextProperty	machtp;

      if (!XGetWMClientMachine(dpy, client, &machtp))
	{
	  machtp.value = NULL;
	  machtp.encoding = None;
	}

      char**	cliargv = NULL;
      int	cliargc;

      if (!XGetCommand(dpy, client, &cliargv, &cliargc))
	{
	  if (machtp.value)
	    XFree((char*)machtp.value);
	  continue;
	}

      XWindowAttributes	wind_info;

      XGetWindowAttributes(dpy, client, &wind_info);
      //std::cout << wind_info.x << " " << wind_info.y << std::endl;
      std::cout << wind_info.width << " " << wind_info.height << std::endl;

      char*	window_name;
      if (XFetchName(dpy, client, &window_name))
	std::cout << std::string(window_name) << std::endl;

      if (machtp.value)
	XFree((char*)machtp.value);
    }

  XCloseDisplay(dpy);

  return 0;
}
