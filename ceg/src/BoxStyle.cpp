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

/************************************************* [ CTOR/DTOR ] *************************************************/

BoxStyle::BoxStyle() :
	_isVisible(true), _opacity(0.5), _imagePath(""), _text(""), _textFont("Arial"), _textFontSize(20), _textColor("black"),  _focusColor("yellow"), _blurColor("black")
{
}

BoxStyle::BoxStyle(QDomElement const & styleElement) :
	_isVisible(true), _opacity(0.5), _imagePath(""), _text(""), _textFont("Arial"), _textFontSize(20), _textColor("black"),  _focusColor("yellow"), _blurColor("black")
{
    this->initializeFromXml(styleElement);
}

void BoxStyle::initializeFromXml(QDomElement const & styleElement)
{
  if (styleElement.hasAttribute("visible"))
    this->_isVisible = styleElement.attribute("visible").toUInt();

  if (styleElement.hasAttribute("opacity"))
    this->_opacity = styleElement.attribute("opacity").toFloat();

  if (styleElement.hasAttribute("imagePath"))
    this->_imagePath = styleElement.attribute("imagePath").toStdString();

  if (styleElement.hasAttribute("text"))
    this->_text = styleElement.attribute("text").toStdString();

  if (styleElement.hasAttribute("font"))
    this->_textFont = styleElement.attribute("font").toStdString();

  if (styleElement.hasAttribute("fontSize"))
    this->_textFontSize = styleElement.attribute("fontSize").toInt();

  if (styleElement.hasAttribute("textColor"))
    this->_textColor = styleElement.attribute("textColor").toStdString();

  if (styleElement.hasAttribute("focusColor"))
    this->_focusColor = styleElement.attribute("focusColor").toStdString();

  if (styleElement.hasAttribute("blurColor"))
    this->_blurColor = styleElement.attribute("blurColor").toStdString();
}

/************************************************* [ GETTERS ] *************************************************/

bool BoxStyle::isVisible() const
{
    return (this->_isVisible);
}

float BoxStyle::getOpacity() const
{
    return (this->_opacity);
}

std::string const & BoxStyle::getImagePath() const
{
    return (this->_imagePath);
}

std::string const & BoxStyle::getText() const
{
    return (this->_text);
}

std::string const & BoxStyle::getTextFont() const
{
    return (this->_textFont);
}

int BoxStyle::getTextFontSize() const
{
    return (this->_textFontSize);
}

std::string const & BoxStyle::getTextColor() const
{
    return (this->_textColor);
}

std::string const & BoxStyle::getFocusColor() const
{
    return (this->_focusColor);
}

std::string const & BoxStyle::getBlurColor() const
{
    return (this->_blurColor);
}
