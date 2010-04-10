#ifndef WIN32EXPLORER_H_

# define WIN32EXPLORER_H_

#include "ICommunicationGraphicalServer.h"


class Win32Explorer : public ICommunicationGraphicalServer
{
public:
	Win32Explorer();
	~Win32Explorer();
    virtual bool	getWindows(std::list<Ceg::Window> &);
    virtual bool	getFocusedWindow(Ceg::Window &);
    virtual bool	setFocusToWindow(Ceg::Window & oldFocusedWindow, Ceg::Window & newFocusedWindow);
    virtual bool	refreshWindowInfo(Ceg::Window &);
    virtual bool	generateClickEvent(short int x, short int y);
	BOOL			fillWindowList(HWND hWnd);

private:
	std::list<Ceg::Window>*	_windowList;
};


#endif //! WIN32EXPLORER_H_