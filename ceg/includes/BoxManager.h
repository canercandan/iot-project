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

class AbstractBox;

class BoxManager
{
public:
  BoxManager();
  ~BoxManager();

  void    getChildren(std::list<QGraphicsRectItem *> &, AbstractBox const *) const;
  void    getParent(std::list<QGraphicsRectItem *> &, AbstractBox const *) const;
  void    getPattern(Ceg::Window const &, std::list<QGraphicsRectItem *> & list) const;

  //! method to import configuration from a XML file to _patterns[name] list
  void    loadConf(const QString& name);
  //! method to save configuration from _patterns[name] list to a XML file (not planned to be used yet!)
  void	  saveConf(const QString& name);

private:
  void    calcChildren(std::list<AbstractBox *> &, QRect const &, unsigned short) const;
  void    calcParent(std::list<AbstractBox *> &, AbstractBox const *) const;
  void    createGraphicItems(std::list<QGraphicsRectItem *> &, std::list<AbstractBox *> const & boxs) const;

private:
  //! this map associates a list of boxes with a context name,
  //! it is initialy filled out by loadConf method
  std::map<std::string, std::list<AbstractBox *> > _patterns;

  static const int NBGRID = 3; // va sauter sera configurable dans l interface.
};

#endif // BOXMANAGER_H
