#include <QtGui>
#include "systray.h"

Systray::Systray()
{
    createActions();
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(networkAction);
    trayIconMenu->addAction(svnAction);
    trayIconMenu->addAction(configAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon = new QSystemTrayIcon(QIcon(":/images/img.png") ,this);
    trayIcon->setContextMenu(trayIconMenu);


    trayIcon->show();
}

void Systray::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible())
    {
	hide();
	event->ignore();
    }
}

void Systray::createActions() // Right click on the systray
{
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    networkAction = new QAction(tr("&Network"), this);
    connect(networkAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    svnAction = new QAction(tr("&SVN"), this);
    connect(svnAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    configAction = new QAction(tr("&Config"), this);
    connect(configAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}
