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
#include <QTranslator>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QSettings>
#include <QDebug>
/*********************************/
#ifndef Q_WS_WIN
# include <log4cxx/xml/domconfigurator.h>
#endif
/*********************************/
#include "Systray.h"
#include "ActionFactory.h"
#include "CancelAction.h"
#include "ClickAction.h"
#include "ExecMenuAction.h"
#include "MoveAction.h"
#include "QuitAction.h"
#include "PopMenuAction.h"
#include "ReadAction.h"
#include "WriteAction.h"
#include "ZoomAction.h"
/*********************************/

#ifndef Q_WS_WIN
#if defined(Q_WS_WIN)
# define LOGCXXCF "../config/log4cxx/WindowsConfig.xml" // Log4cxx Configuration file
#else
# define LOGCXXCF "../config/log4cxx/UnixConfig.xml"
#endif
#endif

int main(int ac, char** av)
{
    //-----------------------------------------------------------------------------
    // Needed Qt information about the project used by QSettings
    //-----------------------------------------------------------------------------

    QCoreApplication::setOrganizationName("IOT");
    QCoreApplication::setOrganizationDomain("ionlythink.com");
    QCoreApplication::setApplicationName("CEG");

    //-----------------------------------------------------------------------------


    QApplication app(ac, av);

    //-----------------------------------------------------------------------------
    // System detection before starting
    //-----------------------------------------------------------------------------

    if (QSystemTrayIcon::isSystemTrayAvailable() == false)
    {
	QMessageBox::critical
		(0,
		 QObject::tr("Systray"),
		 QObject::tr("Couldn't detect any system tray on this system.")
		 );

	return EXIT_FAILURE;
    }

#ifndef Q_WS_WIN
    log4cxx::xml::DOMConfigurator::configure(LOGCXXCF);
#endif

    //-----------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    // Never remove the following line
    //-----------------------------------------------------------------------------

    QApplication::setQuitOnLastWindowClosed(false);

    //-----------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    // Prepare the Action instances
    //-----------------------------------------------------------------------------

    ActionFactory::registerInstantiator(CancelAction::IDENTIFIER, instanciateCancelAction);
    ActionFactory::registerInstantiator(ClickAction::IDENTIFIER, instanciateClickAction);
    ActionFactory::registerInstantiator(ExecMenuAction::IDENTIFIER, instanciateExecMenuAction);
    ActionFactory::registerInstantiator(MoveAction::IDENTIFIER, instanciateMoveAction);
    ActionFactory::registerInstantiator(PopMenuAction::IDENTIFIER, instanciatePopMenuAction);
    ActionFactory::registerInstantiator(QuitAction::IDENTIFIER, instanciateQuitAction);
    ActionFactory::registerInstantiator(ReadAction::IDENTIFIER, instanciateReadAction);
    ActionFactory::registerInstantiator(WriteAction::IDENTIFIER, instanciateWriteAction);
    ActionFactory::registerInstantiator(ZoomAction::IDENTIFIER, instanciateZoomAction);

    //-----------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    // Loading translations
    //-----------------------------------------------------------------------------

    QSettings settings;
    QString language = settings.value("general/language", QLocale::system().name()).toString();

    QTranslator qt_trans;
    QString trans_name = "qt_" + language;
    bool loaded = qt_trans.load(trans_name, QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    if (loaded)
    {
	qDebug() << "Translation" << trans_name << "loaded";
    }
    else
    {
	qDebug() << "Failed to load translation" << trans_name;
    }

    app.installTranslator(&qt_trans);

    QTranslator ceg_tr;
    trans_name = "ceg_" + language;

#if defined(Q_OS_UNIX)
    loaded = ceg_tr.load(trans_name, "/usr/share/ceg/translations");
    if (!loaded)
    {
	loaded = ceg_tr.load(trans_name, "./translations");
    }
#elif defined(Q_OS_WIN)
    loaded = ceg_tr.load(trans_name, "../share/ceg/translations");
    if (!loaded)
    {
	loaded = ceg_tr.load(trans_name, "./translations");
    }
#elif defined(Q_OS_MAC)
    // FIXME i don't know how do this on mac
    loaded = ceg_tr.load(trans_name, "./translations");
#endif

    if (loaded)
    {
	qDebug() << "Translation" << trans_name << "loaded";
    }
    else
    {
	qDebug() << "Failed to load translation" << trans_name;
    }

    app.installTranslator(&ceg_tr);

    //-----------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    // Instanciate the higher object of the program before starting the thread
    //-----------------------------------------------------------------------------

    Systray sytray;

    //-----------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    // Let's start the main thread and return the error code!
    //-----------------------------------------------------------------------------

    return (app.exec());
}
