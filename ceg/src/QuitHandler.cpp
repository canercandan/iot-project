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
#include "QuitHandler.h"
/*********************************/
#include "Singleton.hpp"
#include "Systray.h"
/*********************************/
#include <QDebug>
#include <QApplication>
QuitHandler::QuitHandler(QObject *parent) :
    QObject(parent)
{
    this->connect(qApp,SIGNAL(aboutQuit()), SLOT(handleQuit()));
}

QuitHandler::~QuitHandler()
{
    qDebug() << "destroyed";
    Singleton<Systray>::destroyInstance();
}

void QuitHandler::handleQuit() // FIXME: trouver le moyen dappeler cette methode par les signaux Qt
{
    qDebug() << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII";
    Singleton<Systray>::destroyInstance();
}