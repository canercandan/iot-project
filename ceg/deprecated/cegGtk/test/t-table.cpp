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

#include <gtkmm.h>

int main(int argc, char *argv[])
{
  Gtk::Main	kit(argc, argv);
  Gtk::Window	mywindow;

  Gtk::Table	table(2, 2, true);

  Gtk::Button	button1("(0,1)");
  Gtk::Button	button2("(0,2)");

  mywindow.fullscreen();
  mywindow.set_opacity(0.5);

  mywindow.add(table);

  // widget, left, right, top, bottom
  table.attach(button1, 0, 2, 0, 1);
  //table.attach(button2, 1, 2, 0, 1);

  mywindow.show_all_children();

  Gtk::Main::run(mywindow);

  return 0;
}
