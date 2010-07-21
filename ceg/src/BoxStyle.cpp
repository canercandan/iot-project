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
#include <QStringList>
#include <QDebug>
/*********************************/
#include "BoxStyle.h"
/*********************************/

/************************************************* [ CTOR/DTOR ] *************************************************/

BoxStyle::BoxStyle()
    : _fromXML(false), _isVisible(true), _opacity(0.5), _imagePath(""), _text(""), _textFont("Arial"), _textFontSize(20), _textColor("black"),  _focusColor("yellow"), _blurColor("black")
{
}

BoxStyle::BoxStyle(QDomElement const & styleElement)
    : _fromXML(true), _isVisible(true), _opacity(0.5), _imagePath(""), _text(""), _textFont("Arial"), _textFontSize(20), _textColor("black"),  _focusColor("yellow"), _blurColor("black")
{
    this->initializeFromXml(styleElement);
}

void BoxStyle::initializeFromXml(QDomElement const & styleElement)
{
    //-----------------------------------------------------------------------------
    // We are setting first the parameters with the default values coming
    // from QSettings.
    //-----------------------------------------------------------------------------

    QSettings settings;

    settings.beginGroup("color");
    this->_focusColor = settings.value("focus").toString();
    this->_blurColor = settings.value("blur").toString();
    this->_opacity = settings.value("opacity").toFloat();
    this->_textColor = settings.value("text").toString();
    settings.endGroup();

    //-----------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    // Now we are overwritten the parameters with the values coming from XML.
    //-----------------------------------------------------------------------------

    if (styleElement.hasAttribute("visible"))
        this->_isVisible = styleElement.attribute("visible").toUInt();

    if (styleElement.hasAttribute("opacity"))
        this->_opacity = styleElement.attribute("opacity").toFloat();

    if (styleElement.hasAttribute("imagePath"))
        this->_imagePath = styleElement.attribute("imagePath");

    QString language = settings.value("general/language").toString();
    language = language.split("_")[0];

    if (styleElement.hasAttribute(language + ":text"))
        this->_text = styleElement.attribute(language + ":text");
    else if (styleElement.hasAttribute("text"))
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

    //-----------------------------------------------------------------------------
}

/************************************************* [ GETTERS ] *************************************************/

bool BoxStyle::isVisible() const
{
    return (this->_isVisible);
}

float BoxStyle::getOpacity() const
{
    if ( ! this->_fromXML )
	{
	    QSettings settings;
	    return settings.value("color/opacity").toFloat();
	}

    return this->_opacity;
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

QString BoxStyle::getTextColor() const
{
    if ( ! this->_fromXML )
	{
	    QSettings settings;
	    return settings.value("color/text").toString();
	}

    return this->_textColor;
}

QString BoxStyle::getFocusColor() const
{
    if ( ! this->_fromXML )
	{
	    QSettings settings;
	    return settings.value("color/focus").toString();
	}

    return this->_focusColor;
}

QString BoxStyle::getBlurColor() const
{
    if ( ! this->_fromXML )
	{
	    QSettings settings;
	    return settings.value("color/blur").toString();
	}

    return this->_blurColor;
}
