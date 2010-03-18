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

#include "MenuGrid.h"

MenuGrid::MenuGrid(unsigned int size /*= 3*/)
  : Matrix<MenuArea>(size, 1)
{}

void	MenuGrid::setLabel(unsigned int pos, const Glib::ustring& label)
{
  if (pos >= m_Rows)
    {
      std::clog << "Cannot add label [" << label << "] to the position [" << pos << "]. Not enough place." << std::endl;
      return;
    }

  (*this)[pos][0]->m_Label.set_label(label);
}

void	MenuGrid::on_ok_pressed(GdkEventKey*)
{}
