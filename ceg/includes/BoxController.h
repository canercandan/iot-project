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

#ifndef BOXCONTROLLER_H
#define BOXCONTROLLER_H

#include <map>
#include <list>
#include <string>

class QGraphicsRectItem;

namespace Ceg
{
    class Window;
}

class Box;

/*
  Classe de controle
  Gere tout les patrons (schemas, plan, modele) de logiciels et leur acces, creation
  */

class BoxController
{
public:
    BoxController();
    ~BoxController();

    void    getChildren(std::list<QGraphicsRectItem *> &, Box const *) const; // Retourne le sous patron de la box
    void    getParent(std::list<QGraphicsRectItem *> &, Box const *) const; // Retourne la patron parent a la box
    void    getPattern(Ceg::Window const &, std::list<QGraphicsRectItem *> & list) const; // Retourne la patron du niveau 0
    void    getMenu(std::string const & idMenu, std::list<QGraphicsRectItem *> & menuItems) const; // Retourne les items du menu id

private:
    std::list<Box const *>    getPattern(Box const * boxSearch) const;
    void    initializeFromConfig(QString const & directory = "../config/"); // Lit le repertoire de config pour instancier tout les patrons (custom)
    void    initializeFromXml(QString const & fileName); // Creer la patron present dans le fichier
    void    calcChildren(std::list<Box const *> &, QRect const &, unsigned short) const;
    void    calcParent(std::list<Box const *> &, Box const *) const;
    void    createGraphicItems(std::list<QGraphicsRectItem *> &, std::list<Box const *> const & boxs) const; // Appel la GraphicItemFactory pour toutes les boxs

private:
    //! this map associates a list of boxes with a context name,
    //! it is initialy filled out by loadConf method
    std::map<std::string, std::list<Box const *> > _patterns; // Id du logiciel et son patron associe
    std::map<std::string, std::list<Box const *> > _menus; // Id du menu et son patron associe

    static const int NBGRID = 3; // va sauter sera configurable par le menu des preferences
};

#endif // BOXCONTROLLER_H
