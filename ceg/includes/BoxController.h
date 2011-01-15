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

#include <QList>
#include <QMap>

class QGraphicsRectItem;
class QDir;
class QRect;

class Box;
namespace Ceg
{
    class Window;
}

/**
 * \brief Classe de controle
 * Gere tout les patrons (schemas, plan, modele) de logiciels et leur acces, creation
 */

class BoxController
{
public:
    BoxController();
    ~BoxController();

    void    getChildren(QList<QGraphicsRectItem *> &, Box const *) const; // Retourne le sous patron de la box
    void    getParent(QList<QGraphicsRectItem *> &, Box const *) const; // Retourne la patron parent a la box
    void    getPattern(Ceg::Window const &, QList<QGraphicsRectItem *> & list) const; // Retourne la patron du niveau 0
    void    getMenu(QString const & idMenu, QList<QGraphicsRectItem *> & menuItems) const; // Retourne les items du menu id

private:
    QList<Box const *>  getPattern(Box const * boxSearch) const;
    void    loadConfig(QString const &);
    void    initializeFromConfig(QDir const & directory); // Lit le repertoire de config pour instancier tout les patrons (custom ou menu)
    void    initializeFromXml(QString const & fileName); // Creer la patron present dans le fichier
    void    validXml(QString const & xml_path);
    void    calcChildren(QList<Box const *> &, QRect const &, unsigned short) const;
    void    calcParent(QList<Box const *> &, Box const *) const;
    void    createGraphicItems(QList<QGraphicsRectItem *> &, QList<Box const *> const & boxs) const; // Appel la GraphicItemFactory pour toutes les boxs
    bool    isZoomable(unsigned short level) const; // Methode qui permet de limiter la profondeur de zoom en mode par defaut

private:
    //! this map associates a list of boxes with a context name,
    //! it is initialy filled out by loadConf method
    QMap<QString, QList<Box const *> > _patterns; // Id du logiciel et son patron associe
    QMap<QString, QList<Box const *> > _menus; // Id du menu et son patron associe
    //int                                             _nbSquare; // Nb de boxs utilisees pour le mode par defaut
};

#endif // BOXCONTROLLER_H
