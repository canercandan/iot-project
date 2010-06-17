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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

void mouseClick(int button)
{
  Display *display = XOpenDisplay(NULL);
  XEvent event;

  if (display == NULL)
    {
      fprintf(stderr, "Errore nell'apertura del Display !!!\n");
      exit(EXIT_FAILURE);
    }

  memset(&event, 0x00, sizeof(event));

  event.type = ButtonPress;
  event.xbutton.button = button;
  event.xbutton.same_screen = True;

  XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

  event.xbutton.subwindow = event.xbutton.window;

  while (event.xbutton.subwindow)
    {
      event.xbutton.window = event.xbutton.subwindow;
      XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

  if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)
    fprintf(stderr, "Errore nell'invio dell'evento !!!\n");

  XFlush(display);

  usleep(100000);

  event.type = ButtonRelease;
  event.xbutton.state = 0x100;

  if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)
    fprintf(stderr, "Errore nell'invio dell'evento !!!\n");

  XFlush(display);
  XCloseDisplay(display);
}

int	main(void)
{
  mouseClick(3);

  return (0);
}
