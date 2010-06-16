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

#include <gtkmm.h>

int main(int argc, char *argv[])
{
  Gtk::Main	kit(argc, argv);
  Gtk::Window	mywindow;

  mywindow.set_decorated(false);
  mywindow.set_opacity(0.3);
  mywindow.fullscreen();

  if (mywindow.is_composited())
    std::cout << "is composited" << std::endl;

  Gtk::Main::run(mywindow);

  return 0;
}
