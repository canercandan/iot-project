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

#ifndef MENUITEM_H
#define MENUITEM_H

#include "AbstractItem.h"

class QGraphicsItem;
class QKeyEvent;

/*
Classe de Vue
Vue d'un item(box) de menu
*/

class MenuItem : public AbstractItem
{
public:
    MenuItem(Box const * box, QGraphicsItem * parent = 0);
    ~MenuItem();

protected:
    void keyPressEvent(QKeyEvent * event);
};

#endif // MENUITEM_H
