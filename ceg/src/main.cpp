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

#include <glibmm/optioncontext.h>
#include <glibmm/optiongroup.h>
#include <glibmm/optionentry.h>

#include "WindowManager.h"

#define FILE_TO_LOG	"log.txt"

/**
 * Main function
 */
int	main(int argc, char **argv)
{
  try
    {
      // !both filestr and backup are used for the file logger
      std::ofstream	filestr(FILE_TO_LOG);
      std::streambuf*	backup = std::clog.rdbuf();

      std::clog.rdbuf(filestr.rdbuf());
      std::clog << "#### New session opened ####" << std::endl;

      Glib::OptionContext	oc("Here's the parameters");
      Glib::OptionGroup		og("main", "main description");

      Glib::OptionEntry		verbose;
      verbose.set_long_name("verbose");
      verbose.set_short_name('v');
      verbose.set_description("set verbose level");
      verbose.set_arg_description("verbose level");

      og.add_entry(verbose);

      oc.set_main_group(og);
      oc.set_help_enabled();

      Gtk::Main		kit(argc, argv, oc);
      WindowManager	mywindow;

      Gtk::Main::run();

      std::clog << "#### Session closed ####" << std::endl;
      std::clog.rdbuf(backup);
      filestr.close();
    }
  catch (Glib::OptionError oe)
    {
      std::cerr << "OptionError: " << oe.what() << std::endl;
    }

  return 0;
}
