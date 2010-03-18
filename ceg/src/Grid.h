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

#ifndef GRID_H
#define GRID_H

#include "Matrix.hpp"
#include "Area.h"

/**
 * Grid
 * Represents the default view.
 * We can configure the precision for defining the number of both line and column.
 */
class	Grid : public Matrix<Area>
{
public:
  //! Ctor creating all areas and assigning these into a matrix.
  Grid(unsigned int size = 3);

  //! Key pressed manager to manage the move into matrix and validation to zoom.
  //! The background is also managed.
  //bool	on_key_pressed(GdkEventKey*);

  void	on_ok_pressed(GdkEventKey*);
protected:
  //Gtk::Window	m_ActionWindow;
  //ActionMenu	m_ActionMenu;
};

#endif // !GRID_H
