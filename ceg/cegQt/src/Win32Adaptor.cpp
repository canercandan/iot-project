#include "Win32Adaptor.h"

#include <iostream>

Win32Explorer * Win32Adaptor::_instance = 0;

BOOL	Win32Adaptor::giveWindowList(HWND hWnd, LPARAM lParam)
{
    return (Win32Adaptor::_instance->fillWindowList(hWnd));
}

void	Win32Adaptor::setWin32Explorer(Win32Explorer * instance)
{
    Win32Adaptor::_instance = instance;
}
