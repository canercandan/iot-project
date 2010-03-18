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

#define MATRIX_SIZE 100
#define NUMBER_OF_CASES 20

int main(int argc, char *argv[])
{
  Gtk::Main	kit(argc, argv);
  Gtk::Window	mywindow;

  Gtk::Table	table(MATRIX_SIZE, MATRIX_SIZE, true);

  for (unsigned int i = 0; i < MATRIX_SIZE; ++i)
    {
      for (unsigned int j = 0; j < MATRIX_SIZE; ++j)
	{
	  if (!(i % (MATRIX_SIZE / NUMBER_OF_CASES)) && !(j % (MATRIX_SIZE / NUMBER_OF_CASES)))
	    {
	      Gtk::EventBox* widget = Gtk::manage(new Gtk::EventBox());
	      widget->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("DarkBlue"));
	      table.attach(*widget, i, i + 1, j, j + 1); // attach to grid
	    }
	}
    }

  //mywindow.fullscreen();
  mywindow.set_opacity(0.5);
  mywindow.add(table);
  mywindow.show_all_children();
  //mywindow.set_decorated(false);
  //mywindow.resize(1, 1);
  mywindow.set_size_request(100, 100);

  Gtk::Main::run(mywindow);

  return 0;
}
