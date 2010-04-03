#ifndef WIN32ADAPTOR_H_

# define WIN32ADAPTOR_H_

#include "Win32Explorer.h"

class Win32Adaptor
{
	public:
		static BOOL CALLBACK giveWindowList(HWND hWnd, LPARAM lParam);
		static void	setWin32Explorer(Win32Explorer * instance);
	private:
		static Win32Explorer * _instance;
};

#endif //! WIN32ADAPTOR_H_