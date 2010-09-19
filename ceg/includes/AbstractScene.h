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

#include <QGraphicsScene>
#include <QRect>
#include <QList>

#include "BoxType.h"

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
    AbstractScene(QString const & id, QObject * parent = 0);

    bool    operator==(QString const & id) const;
    bool    operator==(BoxType const & type) const;

    virtual void	    initialize(QList<QGraphicsRectItem *> const & sceneItems); // Ajout des items a la scene

    AbstractItem const *    getCurrentItem() const;
    virtual QRect	    getGeometry() const = 0;
    BoxType                 getType() const;
    QString const &         getId() const;

    virtual IAction *	    keyPressEvent(int key) = 0;
    void                    resetFocusItem(); // Reset le focus sur le premier item de la liste

private:
    void		    clearScene(); // Vide la scene et supprimer les elements

protected:
    BoxType     _type;
    QString     _id; // L'id de la scene, nom du menu ou du programme
};

#endif // ABSTRACTSCENE_H
