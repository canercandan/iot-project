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
#include <QSettings>
/*********************************/
#include "BoxStyle.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

BoxStyle::BoxStyle() :
	_isVisible(true), _opacity(0.5), _imagePath(""), _text(""), _textFont("Arial"), _textFontSize(20), _textColor("black"),  _focusColor("yellow"), _blurColor("black")
{
    QSettings settings;

    this->_focusColor = settings.value("color/focus").toString();
    this->_blurColor = settings.value("color/blur").toString();
    this->_opacity = settings.value("color/opacity").toFloat();
}

BoxStyle::BoxStyle(QDomElement const & styleElement) :
        _isVisible(true), _opacity(0.5), _imagePath(""), _text(""), _textFont("Arial"), _textFontSize(20), _textColor("black"),  _focusColor("yellow"), _blurColor("black")
{
    QSettings settings;

    this->_focusColor = settings.value("color/focus").toString();
    this->_blurColor = settings.value("color/blur").toString();
    this->_opacity = settings.value("color/opacity").toFloat();
    this->initializeFromXml(styleElement);
}

void BoxStyle::initializeFromXml(QDomElement const & styleElement)
{
    if (styleElement.hasAttribute("visible"))
        this->_isVisible = styleElement.attribute("visible").toUInt();

    if (styleElement.hasAttribute("opacity"))
        this->_opacity = styleElement.attribute("opacity").toFloat();

    if (styleElement.hasAttribute("imagePath"))
        this->_imagePath = styleElement.attribute("imagePath");

    if (styleElement.hasAttribute("text"))
        this->_text = styleElement.attribute("text");

    if (styleElement.hasAttribute("font"))
        this->_textFont = styleElement.attribute("font");

    if (styleElement.hasAttribute("fontSize"))
        this->_textFontSize = styleElement.attribute("fontSize").toInt();

    if (styleElement.hasAttribute("textColor"))
        this->_textColor = styleElement.attribute("textColor");

    if (styleElement.hasAttribute("focusColor"))
        this->_focusColor = styleElement.attribute("focusColor");

    if (styleElement.hasAttribute("blurColor"))
        this->_blurColor = styleElement.attribute("blurColor");
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

QString const & BoxStyle::getImagePath() const
{
    return (this->_imagePath);
}

QString const & BoxStyle::getText() const
{
    return (this->_text);
}

QString const & BoxStyle::getTextFont() const
{
    return (this->_textFont);
}

int BoxStyle::getTextFontSize() const
{
    return (this->_textFontSize);
}

QString const & BoxStyle::getTextColor() const
{
    return (this->_textColor);
}

QString const & BoxStyle::getFocusColor() const
{
    return (this->_focusColor);
}

QString const & BoxStyle::getBlurColor() const
{
    return (this->_blurColor);
}
