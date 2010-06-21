// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyleft (C) 2010 CEG development team
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

#ifndef SINGLETON_HPP
# define SINGLETON_HPP

template <typename T>
class Singleton
{
private:
  Singleton(){}
  static T* theInstance;

public:
  static T* getInstance()
  {
    if (theInstance == NULL)
      theInstance = new T();
    return theInstance;
  }

  template <typename C>
  static T* getInstance(C val)
  {
    if (theInstance == 0)
      {
	theInstance = new T(val);
      }
    return theInstance;
  }
};

template <class T>  T* Singleton<T>::theInstance = 0;

#endif /*!SINGLETON_HPP*/
