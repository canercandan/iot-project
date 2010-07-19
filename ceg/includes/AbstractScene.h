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

#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

#include <list>

#include <QGraphicsScene>
#include <QRect>

class QGraphicsRectItem;

class IAction;
class AbstractItem;

/**
 * \brief Classe abstraite implemente des methodes communes aux calques(custom | defaut), menu
 */
 /**
 * Une scene est composee d'items graphiques
 */
class AbstractScene : public QGraphicsScene
{
public:
    AbstractScene(QObject * parent = 0);

    virtual void	    initialize(std::list<QGraphicsRectItem *> const & sceneItems); // Ajout des items a la scene

    AbstractItem const *    getCurrentItem() const;
    virtual QRect	    getGeometry() const = 0;

    virtual IAction *	    keyPressEvent(int key) const = 0;

private:
    void		    clearScene(); // Vide la scene et supprimer les elements
};

#endif // ABSTRACTSCENE_H
