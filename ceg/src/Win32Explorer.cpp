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

#include <QTextStream>
/*********************************/
#include <windows.h>
#include <iostream>
/*********************************/
/*********************************/
#include "Win32Explorer.h"
/*********************************/
#include "Win32Adaptor.h"
#include "ClickAction.h"
/*********************************/
#include "Logger.h"

Win32Explorer::Win32Explorer()
{
}

Win32Explorer::~Win32Explorer()
{
}

bool	Win32Explorer::getWindows(std::list<Ceg::Window> & windowList)
{
    //WNDENUMPROC lpEnumFunc = std::mem_fun(*this, &Win32Explorer::fillWindowList);
    //WNDENUMPROC lpEnumFunc;
    //boost::bind(&Win32Explorer::fillWindowList, this);
    //EnumWindows((&Win32Explorer::fillWindowList), NULL);

    Logger::getInstance()->log(DEBUG_LOG, "GetForegroundWindow()");

    this->_windowList = &windowList;

    Win32Adaptor::setWin32Explorer(this);
    EnumWindows((&Win32Adaptor::giveWindowList), NULL);

    return (true);
}

bool	Win32Explorer::getFocusedWindow(Ceg::Window & oneWindow)
{
    QString msg;
    QTextStream tmp(&msg);
    DWORD dwThreadId, dwProcessId;
    char windowTitle[255];
    //char filenameBuffer[4000];
    HANDLE hProcess;
    HWND hWnd = GetForegroundWindow();
    WINDOWINFO  winInfo;

    if (!GetForegroundWindow())
	return (false);
    if (!hWnd)
	return (false);		// Not a window
    if (!::IsWindowVisible(hWnd))
	return (false);		// Not visible
    if (!GetWindowText(hWnd, windowTitle, sizeof(windowTitle)))
	return (false);		// No window title
    oneWindow.setId(hWnd);
    if (GetWindowInfo(hWnd, &winInfo))
    {
	QRect loadInfo(winInfo.rcClient.left, winInfo.rcClient.top, winInfo.rcClient.right, winInfo.rcClient.bottom);
	oneWindow.setGeometry(loadInfo);
//        tmp << "Pos left: " << winInfo.rcClient.left << std::endl << "Pos TOP : " << winInfo.rcClient.top << std::endl;
//        tmp << "Pos Bottom : " << winInfo.rcClient.bottom << std::endl	<< "Pos right : " << winInfo.rcClient.right << std::endl;
        Logger::getInstance()->log(DEBUG_LOG, msg);
        msg = "";
    }
    dwThreadId = GetWindowThreadProcessId(hWnd, &dwProcessId);
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, dwProcessId);
    //if (!hProcess)
    //	std::cout << "ERROR WITH OPENPROCESS" <<std::endl;
    /*if (::GetModuleFileNameEx(hProcess, NULL, (WCHAR *)filenameBuffer, sizeof(filenameBuffer)) > 0)
    {
	std::cout << "filenameBuffer: " << filenameBuffer << std::endl;
    }
    else*/
    Logger::getInstance()->log(DEBUG_LOG, "MODULEFILENAME FAIL");
    tmp << hWnd << ' ' << dwProcessId << '\t' << windowTitle << "\t\n\n\n";
    Logger::getInstance()->log(DEBUG_LOG, msg);
    CloseHandle(hProcess);
    return (true);
}

bool	Win32Explorer::setFocusToWindow(Ceg::Window & oldFocusedWindow, Ceg::Window & newFocusedWindow)
{
    /*
	* SwitchToThisWindow
	* The SwitchToThisWindow function is called to switch focus to a specified window and bring it to the foreground.
	*/
    return (true);
}


bool	Win32Explorer::refreshWindowInfo(Ceg::Window & window)
{
    QString msg;
    QTextStream tmp(&msg);

    WINDOWINFO  winInfo;
     if (GetWindowInfo(window.getId(), &winInfo))
    {
	QRect refreshInfo(winInfo.rcClient.left, winInfo.rcClient.top, winInfo.rcClient.right, winInfo.rcClient.bottom);
	window.setGeometry(refreshInfo);
        tmp << "Pos left: " << winInfo.rcClient.left << endl  << "Pos TOP : " << winInfo.rcClient.top;
        tmp << "Pos Bottom : " << winInfo.rcClient.bottom << endl << "Pos right : " << winInfo.rcClient.right;
        Logger::getInstance()->log(DEBUG_LOG, msg);
	return (true);
    }
    return (false);
}

bool	Win32Explorer::generateClickEvent(short int buttonID)
{
//     mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE|MOUSEEVENTF_LEFTDOWN,x,y,0,0);
	switch (buttonID)
	{
	case ClickAction::LeftClick:
		mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
		mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
		break;
	case ClickAction::MiddleClick:
		mouse_event(MOUSEEVENTF_MIDDLEDOWN,0,0,0,0);
		mouse_event(MOUSEEVENTF_MIDDLEUP,0,0,0,0);
		break;
	case ClickAction::RightClick:
		mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
		mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);
		break;
	case ClickAction::LeftDbClick:
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

BOOL	Win32Explorer::fillWindowList(HWND hWnd)
{
    QString msg;
    QTextStream tmp(&msg);

    DWORD dwThreadId, dwProcessId;
    char windowTitle[255];
    HANDLE hProcess;
    if (!hWnd)
	return TRUE;		// Not a window
    if (!::IsWindowVisible(hWnd))
	return TRUE;		// Not visible
    if (!GetWindowText(hWnd, windowTitle, sizeof(windowTitle)))
	return TRUE;		// No window title
    WINDOWINFO  winInfo;
    tmp << "Valuer hWind1: " << hWnd;
    Logger::getInstance()->log(DEBUG_LOG, msg);
    msg ="";
    if (GetWindowInfo(hWnd, &winInfo))
    {
	QRect loadInfo(winInfo.rcClient.left, winInfo.rcClient.top, winInfo.rcClient.right, winInfo.rcClient.bottom);
	Ceg::Window newWindow(hWnd, loadInfo, true);
        tmp << "Pos left: " << winInfo.rcClient.left << endl << "Pos TOP : " << winInfo.rcClient.top;
        tmp << "Pos Bottom : " << winInfo.rcClient.bottom << endl << "Pos right : " << winInfo.rcClient.right;
        Logger::getInstance()->log(DEBUG_LOG, msg);
	this->_windowList->push_back(newWindow);
        msg = "";
    }
    tmp << "Valuer hWind2: " << hWnd;
    Logger::getInstance()->log(DEBUG_LOG, msg);

    dwThreadId = GetWindowThreadProcessId(hWnd, &dwProcessId);
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, dwProcessId);
    //if (!hProcess)
    //	std::cout << "ERROR WITH OPENPROCESS" <<std::endl;
    //char filenameBuffer[4000];
    /*if (::GetModuleFileNameEx(hProcess, NULL, (WCHAR *)filenameBuffer, 4000) > 0)
    {
	std::cout << "filenameBuffer: " << filenameBuffer << std::endl;
    }
    else*/
    Logger::getInstance()->log(ERROR_LOG, "MODULEFILENAME FAIL");
    tmp << hWnd << " ProcessId: " << dwProcessId << "\tWinTitle: " << windowTitle << "\t\n\n\n";
    Logger::getInstance()->log(DEBUG_LOG, msg);
    msg = "";
    CloseHandle(hProcess);
    return TRUE;
}
