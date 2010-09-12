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
#include <QMessageBox>
/*********************************/
#include "ZoomAction.h"
/*********************************/
#include "AbstractItem.h"
#include "AbstractScene.h"
#include "MainController.h"
#include "BoxController.h"
#include "Box.h"
/*********************************/
#include "Logger.h"

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * ZoomAction::IDENTIFIER = "Zoom";

ZoomAction::ZoomAction(const QDomElement & actionElement) :
	_zoom(true)
{
    Logger::getInstance()->log(DEBUG_LOG, "ZoomAction::ZoomAction(const QDomElement & actionElement)");
    this->initializeFromXml(actionElement);
}

void ZoomAction::initializeFromXml(const QDomElement & actionElement)
{
    this->_zoom = actionElement.attribute("isZoom").toUInt();
}

/************************************************* [ OTHERS ] *************************************************/

void	ZoomAction::exec(MainController & mainC)
{
    Logger::getInstance()->log(DEBUG_LOG, "ZoomAction::exec");
    /*
    Explication pour la position, quand on est mode custom, l'action est lancee depuis la scene courante, dans le cas du
       mode par defaut, les actions sont lancees depuis les menus et ce sont les menus qui sont en scene courante
       */
    size_t position = (mainC.getCurrentScene()->getType() == CUSTOM_BOX) ? 1 : 2;
    AbstractScene * scene = mainC.getSceneAt(position);
    AbstractItem const * currentItem = scene->getCurrentItem();
    Box const * box = currentItem->getBox();
    QList<QGraphicsRectItem *> graphicItems;
    BoxController const & boxManager = mainC.getBoxController();

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
        mainC.pushFrontScene(scene);
    }
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateZoomAction(const QDomElement & actionElement)
{
    return (new ZoomAction(actionElement));
}
