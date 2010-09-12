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

#ifndef BOX_H_
#define BOX_H_

#include <QRect>
#include <QList>
#include <QMap>

#include "IDomFactory.h"
#include "BoxStyle.h"

class IAction;
class BoxParameter;

enum BoxType {DEFAULT_BOX, CUSTOM_BOX, MENU_BOX};

/**
 * \brief Classe de Modele
 * Classe contenant tout les elements permettant de construire les items graphiques
 */
 /**
 * Element constitutif des patrons
 * Herite de la IDomFactory, car il est possible de creer une box a partir d'un XML
 */
class Box : public IDomFactory
{
public:
    Box(int level, QRect const & geometry); // Utiliser lors des box par defaut, construction des enfants
    Box(QDomElement const & domElement, Box const * parent); // Utiliser pour la creation par XML
    ~Box();

    IAction  *			    getAction() const;
    BoxType			    getBoxType() const;
    QList<Box const *> const &  getChilden() const;
    QRect const &		    getGeometry() const;
    unsigned short		    getLevel() const;
    Box const *			    getParent() const;
    BoxStyle const &		    getGraphicStyle() const;

private:
	virtual void initializeFromXml(QDomElement const & boxElement);
void	createChildren(QDomElement const & childrenElement);

private:
    BoxType		    _type; // Le type de la box
    union
    {
	Box const *	    _parent; // Le parent dans le cas d'une box CUSTOM_BOX
	int		    _level; // La profondeur (de zoom) d'une box DEFAULT_BOX
    }			    _topUnion;
    QRect			    _geometry; // Les dimensions de la boite
    IAction  *		    _action; // L'action que la box entraine
    BoxStyle		    _graphicStyle; // Toutes les options graphiques d'une box
    QList<Box const *>   _children; // le sous patron
};

#endif // BOX_H_
