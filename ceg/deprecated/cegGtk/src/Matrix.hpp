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

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>

#include <gtkmm/table.h>
#include <gdk/gdkkeysyms.h>

#define LEFT	GDK_a // GDK_Left
#define UP	GDK_w // GDK_Up
#define RIGHT	GDK_d // GDK_Right
#define DOWN	GDK_s // GDK_Down
#define OK	GDK_e

//   w e
// a s d

#define AREA_COLOR	Gdk::Color("DarkBlue")

/**
 * Matrix<AreaT>
 */
template <typename AreaT>
class Matrix : public Gtk::Table,
	       public std::vector< std::vector < AreaT* > >
{
public:
  //! Ctor creating all areas and assigning these into a matrix.
  Matrix(unsigned int rows = 3, unsigned int columns = 3);

  //! Key pressed manager to manage the move into matrix and validation to zoom.
  //! The background is also managed.
  bool	on_key_pressed(GdkEventKey*);

  virtual void	on_ok_pressed(GdkEventKey*) = 0;

protected:
  std::pair< unsigned int, unsigned int >	m_Pos; // rows, columns
  unsigned int					m_Rows;
  unsigned int					m_Columns;
};

template <typename AreaT>
Matrix<AreaT>::Matrix(unsigned int rows /*= 3*/, unsigned int columns /*= 3*/)
  : Gtk::Table(rows, columns, true),
    std::vector< std::vector< AreaT* > >(rows, std::vector< AreaT* >(columns, NULL)),
    m_Pos(0, 0), m_Rows(rows), m_Columns(columns)
{
  for (unsigned int i = 0; i < m_Rows; ++i)
    {
      for (unsigned int j = 0; j < m_Columns; ++j)
	{
	  AreaT* widget = Gtk::manage(new AreaT());
	  this->attach(*widget, j, j + 1, i, i + 1); // attach to Gtk::Table
	  (*this)[i][j] = widget;
	}
    }

  (*this)[m_Pos.first][m_Pos.second]->modify_bg(Gtk::STATE_NORMAL, AREA_COLOR);
}

template <typename AreaT>
bool	Matrix<AreaT>::on_key_pressed(GdkEventKey* event)
{
  unsigned int& rows = m_Pos.first;
  unsigned int& columns = m_Pos.second;

  //! first of all we are going to remove the background of the last position in the table
  (*this)[rows][columns]->unset_bg(Gtk::STATE_NORMAL);

  std::clog << "rows[" << rows << "] columns[" << columns << "]" << std::endl;

  if (event->type == GDK_KEY_PRESS)
    {
      if (event->keyval == LEFT)
	{
	  std::clog << "LEFT" << std::endl;
	  columns = (columns == 0) ? m_Columns - 1 : columns - 1;
	}
      else if (event->keyval == UP)
	{
	  std::clog << "UP" << std::endl;
	  rows = (rows == 0) ? m_Rows - 1 : rows - 1;
	}
      else if (event->keyval == RIGHT)
	{
	  std::clog << "RIGHT" << std::endl;
	  columns = (columns + 1 < m_Columns ? columns + 1 : 0);
	}
      else if (event->keyval == DOWN)
	{
	  std::clog << "DOWN" << std::endl;
	  rows = (rows + 1 < m_Rows) ? rows + 1 : 0;
	}
      else if (event->keyval == OK)
	{
	  std::clog << "OK" << std::endl;
	  this->on_ok_pressed(event);
	}
      else
	{
	  std::clog << "key pressed [0x" << std::hex << event->keyval << "]" << std::endl;
	}
    }

  std::clog << "rows[" << rows << "] columns[" << columns << "]" << std::endl;

  (*this)[rows][columns]->modify_bg(Gtk::STATE_NORMAL, AREA_COLOR);

  return true;
}

#endif // !MATRIX_HPP
