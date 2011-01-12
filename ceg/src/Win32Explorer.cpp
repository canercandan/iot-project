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
#include <QTextStream>
/*********************************/
#include <windows.h>
#include <iostream>
/*********************************/
#include "Win32Explorer.h"
/*********************************/
#include "ClickType.h"
#include "Logger.h"
#include "Window.h"
#include "ClickType.h"
/*********************************/

Win32Explorer::Win32Explorer()
{
}

Win32Explorer::~Win32Explorer()
{
}

bool	Win32Explorer::getFocusedWindow(Ceg::Window & oneWindow)
{
  oneWindow.setId(GetFocus());
  return (true);
}

bool	Win32Explorer::setFocusToWindow(Ceg::Window & oldFocusedWindow, Ceg::Window & newFocusedWindow)
{
  HWND hWnd = newFocusedWindow.getId();
  if (oldFocusedWindow.getId() == SetFocus(hWnd))
    {
      return (true);
    }
  else
    {
      return (false);
    }
}

bool	Win32Explorer::generateClickEvent(short int buttonID)
{
    //     mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE|MOUSEEVENTF_LEFTDOWN,x,y,0,0);
    switch (buttonID)
    {
    case LeftClick:
        mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
        break;
    case MiddleClick:
        mouse_event(MOUSEEVENTF_MIDDLEDOWN,0,0,0,0);
        mouse_event(MOUSEEVENTF_MIDDLEUP,0,0,0,0);
        break;
    case RightClick:
        mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
        mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);
        break;
    case LeftDbClick:
        mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
        mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
        break;
    default:
        break;
    }
    return (true);
}

bool Win32Explorer::generateKeybdEvent(quint32 key)
{
    keybd_event(key, VkKeyScan(key), KEYEVENTF_EXTENDEDKEY | 0, 0);
    keybd_event(key, VkKeyScan(key), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    return (true);
}
