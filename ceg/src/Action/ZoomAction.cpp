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
#include <QDomElement>
/*********************************/
#include "ZoomAction.h"
/*********************************/
#include "AbstractItem.h"
#include "AbstractScene.h"
#include "MainController.h"
#include "BoxController.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * ZoomAction::IDENTIFIER = "Zoom";

ZoomAction::ZoomAction(const QDomElement & actionElement)
{
    this->initializeFromXml(actionElement);
}

/************************************************* [ OTHERS ] *************************************************/

bool	ZoomAction::exec(MainController & lm)
{
    AbstractScene * scene = lm.getCurrentScene();
    AbstractItem const * currentItem = scene->getCurrentItem();
    Box const * box = currentItem->getBox();
    std::list<QGraphicsRectItem *> graphicItems;
    BoxController const & boxManager = lm.getBoxController();

    if (this->_zoom == true)
    {
	 boxManager.getChildren(graphicItems, box);
    }
    else
    {
	boxManager.getParent(graphicItems, box);
    }
    if (graphicItems.empty() == false)
    {
	scene->initialize(graphicItems);
    }
    return (true);
}

void ZoomAction::initializeFromXml(const QDomElement & actionElement)
{
    this->_zoom = actionElement.attribute("isZoom").toUInt();
}

IAction * instanciateZoomAction(const QDomElement & actionElement)
{
    return (new ZoomAction(actionElement));
}
