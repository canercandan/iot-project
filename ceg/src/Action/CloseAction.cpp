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
#include "CloseAction.h"
/*********************************/
#include "MainController.h"
#include "AbstractScene.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

char const * CloseAction::IDENTIFIER = "Close";

CloseAction::CloseAction(AbstractScene * sceneToClose) : _sceneToClose(sceneToClose)
{
}

CloseAction::CloseAction(const QDomElement &) : _sceneToClose(0)
{

}

/************************************************* [ OTHERS ] *************************************************/

void	CloseAction::exec(MainController& mainC)
{
    int index = -1;
    if (this->_sceneToClose != 0)
    {
        index = mainC.getIndexOfScene(this->_sceneToClose);
    }
    else // Sinon c'est la scene courante
    {
        int indexDefault = mainC.getFirstOfType(DEFAULT_BOX);
        int indexCustom = mainC.getFirstOfType(CUSTOM_BOX);
        if (indexDefault != -1 && indexCustom != -1)
            index = std::min(indexDefault, indexCustom);
        else
            index = (indexCustom != -1 || indexDefault != -1) ? ((indexCustom != -1) ? indexCustom : indexDefault) : index;
    }
    if (index != -1)
    {
        // remove de la liste + pop du menu home

        // pour le custom
    }
}

void	CloseAction::initializeFromXml(QDomElement const &)
{

}

/************************************************* [ OTHERS ] *************************************************/

IAction * instanciateCloseAction(QDomElement const & actionElement)
{
    return (new CloseAction(actionElement));
}
