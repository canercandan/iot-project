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
#include <QDebug>
/*********************************/
#include "CancelAction.h"
/*********************************/
#include "MainController.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * CancelAction::IDENTIFIER = "Cancel";

CancelAction::CancelAction()
{
}

CancelAction::CancelAction(const QDomElement &)
{

}

void CancelAction::initializeFromXml(const QDomElement &)
{
}

/************************************************* [ OTHERS ] *************************************************/

void    CancelAction::exec(MainController & mainC)
{
    // Le menu est deja cache, donc il n'y a rien a faire
    qDebug() << "CancelAction::exec";
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateCancelAction(QDomElement const & actionElement)
{
    return (new CancelAction(actionElement));
}
