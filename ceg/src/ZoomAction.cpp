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

#include "ZoomAction.h"
#include "LayerManager.h"

ZoomAction::ZoomAction(bool zoom) : _zoom(zoom)
{
}

bool	ZoomAction::exec(LayerManager & lm)
{
    AbstractScene * scene = lm.getCurrentLayer();
    AbstractItem * currentItem = scene->getCurrentItem();
    AbstractBox * box = currentItem->getBox();
    std::list<QGraphicsRectItem *> graphicItems;
    BoxManager * boxManager = lm.getBoxManager();
    if (this->_zoom)
    {
	this->zoom(boxManager, box, graphicItems);
    }
    else
    {
	this->unZoom(boxManager, box, graphicItems);
    }
    scene->initScene(graphicItems);
    return (true);
}

void ZoomAction::zoom(BoxManager * boxManager, AbstractBox * box, std::list<QGraphicsRectItem *> & graphicItems)
{
    boxManager->getChildren(graphicItems, box);
}

void ZoomAction::unZoom(BoxManager * boxManager, AbstractBox * box, std::list<QGraphicsRectItem *> & graphicItems)
{
    boxManager->getParent(graphicItems, box);
}
