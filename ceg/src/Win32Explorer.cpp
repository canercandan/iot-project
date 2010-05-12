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

#include <windows.h>
#include <iostream>

#include "Win32Explorer.h"

#include "Win32Adaptor.h"

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

    std::cout << GetForegroundWindow() << std::endl;

    this->_windowList = &windowList;

    Win32Adaptor::setWin32Explorer(this);
    EnumWindows((&Win32Adaptor::giveWindowList), NULL);

    return (true);
}

bool	Win32Explorer::getFocusedWindow(Ceg::Window & oneWindow)
{
    DWORD dwThreadId, dwProcessId;
    char windowTitle[255];
    char filenameBuffer[4000];
    HANDLE hProcess;
    HWND hWnd = GetForegroundWindow();
    WINDOWINFO  winInfo;

    if (!GetForegroundWindow())
	return (false);
    if (!hWnd)
	return (false);		// Not a window
    if (!::IsWindowVisible(hWnd))
	return (false);		// Not visible
    if (!GetWindowText(hWnd, (WCHAR *)windowTitle, sizeof(windowTitle)))
	return (false);		// No window title
    oneWindow.setId(hWnd);
    if (GetWindowInfo(hWnd, &winInfo))
    {
	QRect loadInfo(winInfo.rcClient.left, winInfo.rcClient.top, winInfo.rcClient.right, winInfo.rcClient.bottom);
	oneWindow.setCharacteristic(loadInfo);
	std::cout << "Pos left: " << winInfo.rcClient.left << std::endl;
	std::cout << "Pos TOP : " << winInfo.rcClient.top << std::endl;
	std::cout << "Pos Bottom : " << winInfo.rcClient.bottom << std::endl;
	std::cout << "Pos right : " << winInfo.rcClient.right << std::endl;
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
	std::cout << "MODULEFILENAME FAIL" << std::endl;
    std::cout << hWnd << ' ' << dwProcessId << '\t' << windowTitle << "\t\n\n\n" << std::endl;
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
    WINDOWINFO  winInfo;
    if (GetWindowInfo(window.getId(), &winInfo))
    {
	QRect refreshInfo(winInfo.rcClient.left, winInfo.rcClient.top, winInfo.rcClient.right, winInfo.rcClient.bottom);
	window.setCharacteristic(refreshInfo);
	std::cout << "Pos left: " << winInfo.rcClient.left << std::endl;
	std::cout << "Pos TOP : " << winInfo.rcClient.top << std::endl;
	std::cout << "Pos Bottom : " << winInfo.rcClient.bottom << std::endl;
	std::cout << "Pos right : " << winInfo.rcClient.right << std::endl;
	return (true);
    }
    return (false);
}

bool	Win32Explorer::generateClickEvent(short int buttonID)
{
    (void)buttonID;
//     mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE|MOUSEEVENTF_LEFTDOWN,x,y,0,0);
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
    return (true);
}

BOOL	Win32Explorer::fillWindowList(HWND hWnd)
{
    DWORD dwThreadId, dwProcessId;
    char windowTitle[255];
    HANDLE hProcess;
    if (!hWnd)
	return TRUE;		// Not a window
    if (!::IsWindowVisible(hWnd))
	return TRUE;		// Not visible
    if (!GetWindowText(hWnd, (WCHAR *)windowTitle, sizeof(windowTitle)))
	return TRUE;		// No window title
    WINDOWINFO  winInfo;
    std::cout << "Valuer hWind1: " << hWnd << std::endl;
    if (GetWindowInfo(hWnd, &winInfo))
    {
	QRect loadInfo(winInfo.rcClient.left, winInfo.rcClient.top, winInfo.rcClient.right, winInfo.rcClient.bottom);
	Ceg::Window newWindow(hWnd, loadInfo, true);
	std::cout << "Pos left: " << winInfo.rcClient.left << std::endl;
	std::cout << "Pos TOP : " << winInfo.rcClient.top << std::endl;
	std::cout << "Pos Bottom : " << winInfo.rcClient.bottom << std::endl;
	std::cout << "Pos right : " << winInfo.rcClient.right << std::endl;
	this->_windowList->push_back(newWindow);
    }

    std::cout << "Valuer hWind2: " << hWnd << std::endl;

    dwThreadId = GetWindowThreadProcessId(hWnd, &dwProcessId);
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, dwProcessId);
    //if (!hProcess)
    //	std::cout << "ERROR WITH OPENPROCESS" <<std::endl;
    char filenameBuffer[4000];
    /*if (::GetModuleFileNameEx(hProcess, NULL, (WCHAR *)filenameBuffer, 4000) > 0)
    {
	std::cout << "filenameBuffer: " << filenameBuffer << std::endl;
    }
    else*/
	std::cout << "MODULEFILENAME FAIL" << std::endl;
    std::cout << hWnd << " ProcessId: " << dwProcessId << "\tWinTitle: " << windowTitle << "\t\n\n\n" << std::endl;
    CloseHandle(hProcess);
    return TRUE;
}
