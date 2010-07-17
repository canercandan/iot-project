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
#include <vector>
/*********************************/
#include <QApplication>
#include <QTranslator>
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
#include "ClickAction.h"
#include "ExecMenuAction.h"
#include "MoveAction.h"
#include "PopMenuAction.h"
#include "ReadAction.h"
#include "ZoomAction.h"
/*********************************/

#ifndef Q_WS_WIN
#if defined(Q_WS_WIN)
# define LOGCXXCF "../config/log4cxx/WindowsConfig.xml" // Log4cxx Configuration file
#else
# define LOGCXXCF "../config/log4cxx/UnixConfig.xml"
#endif
#endif

static bool configure_language(QApplication& app, QTranslator& translator)
{
    QSettings settings;

    unsigned int languageID(settings.value("general/language").toUInt());

    std::vector< QString > languages (2);

    languages[0] = "en_US";
    languages[1] = "fr";

    if (languageID >= languages.size())
	return false;

    translator.load(QString(":/translations/translations/ceg_") + languages[ languageID ]);
    app.installTranslator(&translator);

    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("IOT");
    QCoreApplication::setOrganizationDomain("ionlythink.com");
    QCoreApplication::setApplicationName("CEG");

    QApplication app(argc, argv);

    if (QSystemTrayIcon::isSystemTrayAvailable() == false)
	{
	    QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("Couldn't detect any system tray on this system."));
	    return (EXIT_FAILURE);
	}

#ifndef Q_WS_WIN
    log4cxx::xml::DOMConfigurator::configure(LOGCXXCF);
#endif

    QApplication::setQuitOnLastWindowClosed(false); // Ne jamais retire cette ligne

    ActionFactory::registerInstantiator(ClickAction::IDENTIFIER, instanciateClickAction);
    ActionFactory::registerInstantiator(ExecMenuAction::IDENTIFIER, instanciateExecMenuAction);
    ActionFactory::registerInstantiator(MoveAction::IDENTIFIER, instanciateMoveAction);
    ActionFactory::registerInstantiator(PopMenuAction::IDENTIFIER, instanciatePopMenuAction);
    ActionFactory::registerInstantiator(ReadAction::IDENTIFIER, instanciateReadAction);
    ActionFactory::registerInstantiator(ZoomAction::IDENTIFIER, instanciateZoomAction);

    QTranslator	translator;

    if (!configure_language(app, translator))
    	return -1;

    Systray sytray;
    qDebug() << QLocale::system().name() << " - la langue = " << QLocale::system().languageToString(QLocale::system().language());
    return (app.exec());
}
