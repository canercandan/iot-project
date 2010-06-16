// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyleft (C) 2010 CEG development team
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

/*********************************/
#include <QApplication>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QDebug>
/*********************************/
#include "Singleton.hpp"
#include "MainController.h"
#include "Systray.h"
#include "ActionFactory.h"
#include "ClickAction.h"
#include "ExecMenuAction.h"
#include "MoveAction.h"
#include "PopMenuAction.h"
#include "ReadAction.h"
#include "ZoomAction.h"
/*********************************/

// int main(int argc, char *argv[])
// {
//   QApplication a(argc, argv);

//   if (QSystemTrayIcon::isSystemTrayAvailable() == false)
//     {
//       QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("Couldn't detect any system tray on this system."));
//       return (EXIT_FAILURE);
//     }
//   QApplication::setQuitOnLastWindowClosed(false);

//   ActionFactory::registerInstantiator(ClickAction::IDENTIFIER, instanciateClickAction);
//   ActionFactory::registerInstantiator(ExecMenuAction::IDENTIFIER, instanciateExecMenuAction);
//   ActionFactory::registerInstantiator(MoveAction::IDENTIFIER, instanciateMoveAction);
//   ActionFactory::registerInstantiator(PopMenuAction::IDENTIFIER, instanciatePopMenuAction);
//   ActionFactory::registerInstantiator(ReadAction::IDENTIFIER, instanciateReadAction);
//   ActionFactory::registerInstantiator(ZoomAction::IDENTIFIER, instanciateZoomAction);
//   Systray * systray = Singleton<Systray>::getInstance();
//   return (a.exec());
// }

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  qDebug() << "\n\n";
  ActionFactory::registerInstantiator(ClickAction::IDENTIFIER, instanciateClickAction);
  ActionFactory::registerInstantiator(ExecMenuAction::IDENTIFIER, instanciateExecMenuAction);
  ActionFactory::registerInstantiator(MoveAction::IDENTIFIER, instanciateMoveAction);
  ActionFactory::registerInstantiator(PopMenuAction::IDENTIFIER, instanciatePopMenuAction);
  ActionFactory::registerInstantiator(ReadAction::IDENTIFIER, instanciateReadAction);
  ActionFactory::registerInstantiator(ZoomAction::IDENTIFIER, instanciateZoomAction);
  ActionFactory::printRegisterInstantiator();
  MainController lm;
  lm.start();
  return a.exec();
}
