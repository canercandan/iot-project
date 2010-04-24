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

#ifndef WINDOWGEOMETRY_H_
#define WINDOWGEOMETRY_H_

/*! \class BasicWindowInfo
 * \brief Class regroupant toutes les informations basiques communes a toutes fenetres affiches a l ecran
 */
class WindowGeometry
{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe BasicWindowInfo
     *
     */
    WindowGeometry(short int x = 0, short int y = 0, short int width = 0, short int height = 0);

public:
    short int _x; /*!< Position absolue sur l'axe des abscisses du coint haut gauche de la fenetre */
    short int _y; /*!< Position absolue sur l'axe des ordonnes du coint haut gauche de la fenetre */
    short int _width; /*!< Largeur de la fenetre */
    short int _height; /*!< Hauteur de la fenetre */
};

#endif // WINDOWGEOMETRY_H_
