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


#ifndef BOXSTYLE_H
#define BOXSTYLE_H

#include <string>

#include "IDomFactory.h"

/*
  Classe de modele
  Contient toute les aspect relatif au graphisme d'une box
  Herite de la IDomFactory, car il est possible de creer une box a partir d'un XML
  */
class BoxStyle : public IDomFactory
{
public:
    BoxStyle();
    BoxStyle(QDomElement const &);

private:
    virtual void initializeFromXml(QDomElement const &);

private:
    bool    _isVisible;
    float   _opacity;
    std::string _imagePath;
    std::string _text;
    std::string _textFont;
    int	_focusColor;
    int _blurColor;
};

#endif // BOXSTYLE_H
