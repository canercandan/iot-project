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

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <vector>
#include <fstream>
#include <list>

#include <gtkmm/window.h>
#include <gtkmm/statusicon.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/toggleaction.h>

#include "Layer.h"
#include "MenuWindow.h"

/**
 * WindowManager
 * Main window of the project
 */
class WindowManager : public Gtk::Window
{
public:
  /**
   * Ctor configures main window and children parameters
   */
  WindowManager();

protected:
  //! Methods
  virtual void show_popup_menu(guint button, guint activate_time);

  void	on_FreeBrowsing_toggled();
  void	on_EventMenu_toggled();
  void	on_NavigationMenu_toggled();

protected:
  Glib::RefPtr<Gtk::StatusIcon>		m_refStatusIcon;
  Glib::RefPtr<Gtk::UIManager>		m_refUIManager;

  Glib::RefPtr<Gtk::ToggleAction>	m_refFreeBrowsing;
  Glib::RefPtr<Gtk::ToggleAction>	m_refEventMenu;
  Glib::RefPtr<Gtk::ToggleAction>	m_refNavigationMenu;

  std::list<Layer*>	m_layers;

  Layer			m_FreeBrowsing;
  MenuWindow		m_EventMenuWindow;
  MenuWindow		m_NavigationMenuWindow;

  friend void	on_statusicon_popup(GtkStatusIcon*, guint button, guint activate_time, gpointer object);
};

//! Statusicon (GTK+) callbacks:
void	on_statusicon_activated(GtkWidget*, gpointer object);
void	on_statusicon_popup(GtkStatusIcon*, guint button, guint activate_time, gpointer object);

/**
 * \example main.cpp
 * This is an example of how to implement Windowmanager class.
 */

#endif //WINDOWMANAGER_H
