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
#include "Window.h"
/*********************************/

namespace Ceg
{
    /************************************************* [ CTOR/DTOR ] *************************************************/

    Window::Window() :
	    _programName(), _id(0), _geometry(), _isVisible(false)
    {

    }

    Window::Window(WindowId windowId, QRect const & windoInfo, bool visibility, std::string const & programName) :
	    _programName(programName), _id(windowId), _geometry(windoInfo), _isVisible(visibility)
    {
    }

    /************************************************* [ GETTERS ] *************************************************/

    WindowId Window::getId() const
    {
	return (this->_id);
    }

    QRect const & Window::getGeometry() const
    {
	return (this->_geometry);
    }

    std::string const & Window::getProgramName() const
    {
	return (this->_programName);
    }

    /************************************************* [ SETTERS ] *************************************************/

    void Window::setGeometry(QRect const & rhs)
    {
	this->_geometry = rhs;
    }

    void Window::setId(WindowId id)
    {
	this->_id = id;
    }
}
