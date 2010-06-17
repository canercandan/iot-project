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

#ifndef LAYER_H
#define LAYER_H

#include "AbstractScene.h"
#include "Window.h"

class IAction;

/*
  Classe de Vue
  Represente le calque d'une fenetre
  */
class Layer : public AbstractScene
{
public:
    Layer(Ceg::Window const &);
    ~Layer();

    virtual QRect	getGeometry() const;
    virtual IAction *	keyPressEvent(int key) const;
    virtual void	initialize(std::list<QGraphicsRectItem *> const & sceneItems); // Ajout des items a la scene

private:
    IAction *		moveVertically() const; // Gere le mouvement vertical
    IAction *		moveHorizontally() const; // Gere le mouvement horizontal

private:
    Ceg::Window _host; // la fenetre qui est calquee
    IAction *	_menuAction; // Correspond a l'action retourne lorsque l'utilisateur sort du calque seulement dans le cas de la navigation par defaut
};

#endif // LAYER_H