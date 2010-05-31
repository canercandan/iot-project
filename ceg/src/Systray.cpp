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

/*********************************/
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QMessageBox>
#include <QApplication>
/*********************************/
#include "Systray.h"
/*********************************/
#include "LayerManager.h"
/*********************************/

Systray::Systray(QWidget *parent) :
	QWidget(parent), _lm(new LayerManager)
{
    this->_trayIcon = new QSystemTrayIcon(QIcon(":/images/systray-transparent-32x32.png"), this);
    this->_trayIconMenu = new QMenu(this);
    this->_startAction = new QAction("Start", this);
    this->_settingAction = new QAction("Setting", this);
    this->_aboutQtAction = new QAction("About Qt", this);
    this->_aboutCegAction = new QAction("About Ceg", this);
    this->_quitAction = new QAction("Quit", this);

    this->_trayIconMenu->addAction(this->_startAction);
    this->_trayIconMenu->addAction(this->_settingAction);
    this->_trayIconMenu->addAction(this->_aboutCegAction);
    this->_trayIconMenu->addAction(this->_aboutQtAction);
    this->_trayIconMenu->addSeparator();
    this->_trayIconMenu->addAction(this->_quitAction);

    this->_trayIcon->setContextMenu(this->_trayIconMenu);
    qApp->connect(this->_quitAction, SIGNAL(triggered()), SLOT(quit()));
    this->connect(this->_startAction, SIGNAL(triggered()), SLOT(on__startAction_triggered()));
    this->connect(this->_aboutCegAction, SIGNAL(triggered()), SLOT(on__aboutCegAction_triggered()));
    this->connect(this->_aboutQtAction, SIGNAL(triggered()), SLOT(on__aboutQtAction_triggered()));
    this->connect(this->_settingAction, SIGNAL(triggered()), SLOT(on__settingAction_triggered()));
    this->_trayIcon->show();
    this->_trayIcon->showMessage("Information Message", "Click on Start to launch the Default Navigator", QSystemTrayIcon::MessageIcon(), 7000);
}

Systray::~Systray()
{
    delete this->_lm;
}

void Systray::on__startAction_triggered()
{
    QString content;
    if (this->_startAction->text() == "Start")
    {
	QMessageBox::information(0, "Commandes", "Left | Right arrow = Horizontal Move\nUp | Down Arrow = Vertical move\nEnter = Zoom\nBackspace = unzoom\n1 = Simple Click\nAlt + F4 = Quit");
	this->_lm->start();
	content = "Stop";
    }
    else
    {
	this->_lm->stop();
	content = "Start";
    }
    this->_startAction->setText(content);
}

void Systray::on__aboutQtAction_triggered()
{
    QMessageBox::aboutQt(0, "About Qt");
}

void Systray::on__settingAction_triggered()
{
    QMessageBox::information(0, "Setting", "une widget qui permet de mettre les options");
}

void Systray::on__aboutCegAction_triggered()
{
    QMessageBox::information(0, "About CEG", "Des infos sur le CEG...");
}
