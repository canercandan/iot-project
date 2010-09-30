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
#include "KeyboardAction.h"
/*********************************/
#include "ActionFactory.h"
#include "AbstractItem.h"
#include "Box.h"
#include "MainController.h"
#include "AbstractScene.h"
#include "ICommunicationGraphicalServer.h"
#include "Utils.h"
#include "Logger.h"
#include "ClickType.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * KeyboardAction::IDENTIFIER = "Keyboard";

KeyboardAction::KeyboardAction(const QDomElement & actionElement) : _keys("")
{
    Logger::getInstance()->log(DEBUG_LOG, "KeyboardAction::KeyboardAction");
    this->initializeFromXml(actionElement);
}

void KeyboardAction::initializeFromXml(const QDomElement & domElement)
{
    if (domElement.hasAttribute("press") == true)
        this->_keys = domElement.attribute("press");
}

/************************************************* [ OTHERS ] *************************************************/
#include <QDebug>
void	KeyboardAction::exec(MainController & mainC)
{
  Logger::getInstance()->log(DEBUG_LOG, "KeyboardAction::exec");
  /*
    Explication pour la position, quand on est mode custom, l'action est lancee depuis la scene courante, dans le cas du
    mode par defaut, les actions sont lancees depuis les menus et ce sont les menus qui sont en scene courante
  */
  size_t position = (mainC.getCurrentScene()->getType() == CUSTOM_BOX) ? 1 : 2;
  AbstractScene * scene = mainC.getSceneAt(position);
  AbstractItem const * ai = scene->getCurrentItem();
  Box const *	ab = ai->getBox();

  if (ab == 0)
    return ;

  QCursor::setPos(ab->getGeometry().center());
  qDebug() << "Geometry en " << ab->getGeometry().center();

  mainC.getView().hide(); // On cache la vue pour cliquer sur le programme et non pas notre application
  ICommunicationGraphicalServer * comGs = mainC.getComGs();
  comGs->generateClickEvent(LeftClick); // On genere un click pour donner le focus a la zone dans laquelle on souhaite ecrire
  for (int i = 0, sizeString = this->_keys.size(); i < sizeString; ++i) // On genere toutes les touches clavier
    {
      comGs->generateKeybdEvent(this->_keys.at(i).toAscii());
    }
  mainC.getView().show(); // On reaffiche le ceg
  QRect const & geometry = mainC.getCurrentScene()->getCurrentItem()->getBox()->getGeometry();
  QCursor::setPos(geometry.center());
  qDebug() << "Click generer " << geometry.center() << "- Nom de la scene courante = " << mainC.getCurrentScene()->getId();
  qDebug() << "ATTEENNTION : " << "pos = " << mainC.getCurrentScene()->getCurrentItem()->pos() << " scene pos" << mainC.getCurrentScene()->getCurrentItem()->scenePos()<< " bounding scene pos" << mainC.getCurrentScene()->getCurrentItem()->sceneBoundingRect();
  //  comGs->generateClickEvent(LeftClick); // On genere un click pour etre sure de redonner le focus au ceg, car il arrive de temps que l'on perde le focus lorsqu'on tape une touche
}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateKeyboardAction(QDomElement const & actionElement)
{
    return (new KeyboardAction(actionElement));
}
