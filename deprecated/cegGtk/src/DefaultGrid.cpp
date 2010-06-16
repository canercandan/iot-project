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

#include "DefaultGrid.h"

DefaultGrid::DefaultGrid(unsigned int size)
  : Grid(size)
{}

void	DefaultGrid::on_ok_pressed(GdkEventKey*)
{
  Glib::RefPtr<Gdk::Window> window = this->get_window();
  Gtk::Allocation alloc = (*this)[m_Pos.first][m_Pos.second]->get_allocation();
  int x, y, width, height, win_x, win_y;

  window->unfullscreen();
  window->get_origin(win_x, win_y);
  x = alloc.get_x() + win_x;
  y = alloc.get_y() + win_y;
  width = alloc.get_width();
  height = alloc.get_height();
  window->move(x, y);
  window->resize(width, height);
}
