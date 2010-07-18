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

#include <QDomElement>

#include "WriteAction.h"

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * WriteAction::IDENTIFIER = "Write";

WriteAction::WriteAction(QDomElement const & domElement) : _toWrite()
{
    this->initializeFromXml(domElement);
}

void	WriteAction::initializeFromXml(QDomElement const & domElement)
{
    this->_toWrite = domElement.attribute("buffer").toStdString();
}

/************************************************* [ OTHERS ] *************************************************/

void	WriteAction::exec(MainController &)
{
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateWriteAction(const QDomElement & actionElement)
{
    return (new WriteAction(actionElement));
}
