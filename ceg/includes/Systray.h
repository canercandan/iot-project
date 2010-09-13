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

#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QWidget>

#include "MainController.h"

class QSystemTrayIcon;
class QMenu;
class QAction;

/**
 * \brief Classe de vue qui contient le Systray.
 * Elle permet de stopper le Ceg
 * Permet d'activer/desactiver la navigation
 * Permet d'acceder au menu de preferences et autres reglages
 */
class Systray : public QWidget
{
    Q_OBJECT
public:
    explicit Systray(QWidget *parent = 0);
    ~Systray();

signals:
    void navigationStarted();
    void navigationStoped();

public slots:
    void on__startAction_triggered();

private slots:
    void on__aboutQtAction_triggered();
    void on__settingAction_triggered();
    void on__aboutCegAction_triggered();

private:
    MainController 	_mainC;
    QSystemTrayIcon *	_trayIcon;
    QMenu *		_trayIconMenu;
    QAction *		_startAction;
    QAction *		_settingAction;
    QAction *		_aboutQtAction;
    QAction *		_aboutCegAction;
    QAction *		_quitAction;
};

#endif // SYSTRAY_H
