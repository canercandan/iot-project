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

#ifndef BOXMANAGER_H
#define BOXMANAGER_H

#include <map>
#include <list>
#include <string>

class QGraphicsRectItem;

namespace Ceg
{
    class Window;
}

class Box;

class BoxManager
{
public:
  BoxManager();
  ~BoxManager();

  void    getChildren(std::list<QGraphicsRectItem *> &, Box const *) const;
  void    getParent(std::list<QGraphicsRectItem *> &, Box const *) const;
  void    getPattern(Ceg::Window const &, std::list<QGraphicsRectItem *> & list) const;

  //! method to import configuration from a XML file to _patterns[name] list
  void    loadConf(const QString& name);

private:
  void    calcChildren(std::list<Box *> &, QRect const &, unsigned short) const;
  void    calcParent(std::list<Box *> &, Box const *) const;
  void    createGraphicItems(std::list<QGraphicsRectItem *> &, std::list<Box *> const & boxs) const;

private:
  //! this map associates a list of boxes with a context name,
  //! it is initialy filled out by loadConf method
  std::map<std::string, std::list<Box *> > _patterns;

  static const int NBGRID = 3; // va sauter sera configurable dans l interface.
};

#endif // BOXMANAGER_H
