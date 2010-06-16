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

#include "ActionMenu.h"

ActionMenu::ActionMenu()
//: m_ZoomButton("Zoom"), m_ClickButton("Click"), m_BackButton("Back"), m_HideButton("Hide")
  : Matrix<Area>(4, 1)
{
  //this->set_position(Gtk::WIN_POS_CENTER_ON_PARENT);
  this->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  this->set_keep_above(true);
  this->set_decorated(false);

//   m_Vertical.add(m_ZoomButton);
//   m_Vertical.add(m_ClickButton);
//   m_Vertical.add(m_BackButton);
//   m_Vertical.add(m_HideButton);

//   this->add(m_Vertical);
//   this->show_all_children();
}
