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

/*********************************/
#include <QDomElement>
/*********************************/
#include "BoxStyle.h"
/*********************************/

// FIXME: utiliser le font avec QPainter.setFont()

#include <QDebug>

BoxStyle::BoxStyle() :
  _isVisible(true), _opacity(0.5), _imagePath(""), _text(""), _textFont(""), _textFontSize(20), _textColor("black"),  _focusColor("yellow"), _blurColor("black")
{
  qDebug() << "in ctor";
}

BoxStyle::BoxStyle(QDomElement const & styleElement)
{
    this->initializeFromXml(styleElement);
}

#include <QDebug>

void BoxStyle::initializeFromXml(QDomElement const & styleElement)
{
  if (styleElement.hasAttribute("visible") == true)
    {this->_isVisible = styleElement.attribute("visible").toUInt();}
  else
    {
      qDebug() << "COUCOU";
      qDebug() << _isVisible;
    }

    this->_opacity = styleElement.attribute("opacity").toFloat();
    this->_imagePath = styleElement.attribute("imagePath").toStdString();
    this->_text = styleElement.attribute("text").toStdString();
    this->_textFont = styleElement.attribute("font").toStdString();
    this->_textFontSize = styleElement.attribute("fontSize").toInt();
    this->_textColor = styleElement.attribute("textColor").toStdString();
    this->_focusColor = styleElement.attribute("focusColor").toStdString();
    this->_blurColor = styleElement.attribute("blurColor").toStdString();
}

// ATTRIBUTES GETTER

bool BoxStyle::isVisible() const {return _isVisible;}
float BoxStyle::getOpacity() const {return _opacity;}
std::string BoxStyle::getImagePath() const {return _imagePath;}
std::string BoxStyle::getText() const {return _text;}
std::string BoxStyle::getTextFont() const {return _textFont;}
int BoxStyle::getTextFontSize() const {return _textFontSize;}
std::string BoxStyle::getTextColor() const {return _textColor;}
std::string BoxStyle::getFocusColor() const {return _focusColor;}
std::string BoxStyle::getBlurColor() const {return _blurColor;}

// END ATTRIBUTES GETTER
