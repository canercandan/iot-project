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

#include <gtkmm/main.h>
#include <gtkmm/actiongroup.h>
#include <gtkmm/action.h>
#include <gtkmm/stock.h>

#include "WindowManager.h"
#include "DefaultGrid.h"
#include "EventMenuGrid.h"
#include "NavigationMenuGrid.h"

WindowManager::WindowManager()
  : m_FreeBrowsing(new DefaultGrid(3)),
    m_EventMenuWindow(new EventMenuGrid),
    m_NavigationMenuWindow(new NavigationMenuGrid)
{
  this->set_title("CEG - GEC");

  m_FreeBrowsing.fullscreen();
  //m_FreeBrowsing.maximize();

  //m_FreeBrowsing.show();
  //m_EventMenuWindow.show();
  //m_NavigationMenuWindow.show();

  std::clog << std::boolalpha << "is composited: "
	    << this->is_composited() << std::endl;

  Glib::RefPtr<Gtk::ActionGroup>	refActionGroup = Gtk::ActionGroup::create();

  m_refFreeBrowsing = Gtk::ToggleAction::create("FreeBrowsing", "Free Browsing", "", m_FreeBrowsing.is_visible());
  m_refEventMenu = Gtk::ToggleAction::create("EventMenu", "Event Menu", "", m_EventMenuWindow.is_visible());
  m_refNavigationMenu = Gtk::ToggleAction::create("NavigationMenu", "Navigation Menu", "", m_NavigationMenuWindow.is_visible());

  refActionGroup->add(m_refFreeBrowsing);
  refActionGroup->add(m_refEventMenu);
  refActionGroup->add(m_refNavigationMenu);
  refActionGroup->add(Gtk::Action::create("Quit", Gtk::Stock::QUIT), sigc::ptr_fun(&Gtk::Main::quit));

  m_refFreeBrowsing->signal_toggled().connect(sigc::mem_fun(*this, &WindowManager::on_FreeBrowsing_toggled));
  m_refEventMenu->signal_toggled().connect(sigc::mem_fun(*this, &WindowManager::on_EventMenu_toggled));
  m_refNavigationMenu->signal_toggled().connect(sigc::mem_fun(*this, &WindowManager::on_NavigationMenu_toggled));

  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(refActionGroup);

  Glib::ustring	ui_info =
    "<ui>"
    "  <popup name='Popup'>"
    "    <menuitem action='FreeBrowsing'/>"
    "    <menuitem action='EventMenu'/>"
    "    <menuitem action='NavigationMenu'/>"
    "    <separator/>"
    "    <menuitem action='Quit'/>"
    "  </popup>"
    "</ui>"
    ;

  m_refUIManager->add_ui_from_string(ui_info);

  m_refStatusIcon = Gtk::StatusIcon::create(Gtk::Stock::HOME);
  m_refStatusIcon->set_tooltip("CEG - GEC");

  GtkStatusIcon* gobj_StatusIcon = m_refStatusIcon->gobj();
  g_signal_connect(G_OBJECT(gobj_StatusIcon), "activate", G_CALLBACK(on_statusicon_activated), this);
  g_signal_connect(G_OBJECT(gobj_StatusIcon), "popup-menu", G_CALLBACK(on_statusicon_popup), this);

  //this->show_all_children();
}

void	WindowManager::show_popup_menu(guint button, guint activate_time)
{
  Gtk::Menu*	pMenu = static_cast<Gtk::Menu*>(m_refUIManager->get_widget("/Popup"));
  if(pMenu)
    pMenu->popup(button, activate_time);
}

#include <iomanip>

void	WindowManager::on_FreeBrowsing_toggled()
{
  m_refFreeBrowsing->get_active() ? m_FreeBrowsing.show() : m_FreeBrowsing.hide();
}

void	WindowManager::on_EventMenu_toggled()
{
  m_refEventMenu->get_active() ? m_EventMenuWindow.show() : m_EventMenuWindow.hide();
}

void	WindowManager::on_NavigationMenu_toggled()
{
  m_refNavigationMenu->get_active() ? m_NavigationMenuWindow.show() : m_NavigationMenuWindow.hide();
}

void	on_statusicon_activated(GtkWidget* widget, gpointer object)
{
  Gtk::Window* window = static_cast<Gtk::Window*>(object);
  bool hided = window->get_skip_taskbar_hint();
  hided ? window->deiconify() : window->iconify();
  window->set_skip_taskbar_hint(not hided);
}

void	on_statusicon_popup(GtkStatusIcon* status_icon, guint button,
			    guint activate_time, gpointer object)
{
  return static_cast<WindowManager*>(object)->show_popup_menu(button, activate_time);
}
