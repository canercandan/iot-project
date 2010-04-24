#ifndef XWINDOWSYSTEM_H_
#define XWINDOWSYSTEM_H_

#include "ICommunicationGraphicalServer.h"

#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xmu/WinUtil.h>

/* doc pour l'API http://tronche.com/gui/x/xlib/
 * ressource tres utile http://standards.freedesktop.org/wm-spec/1.3/ar01s05.html
 * pour recupere le PID du programme http://lists.samba.org/archive/linux/2008-July/020298.html  _NET_WM_PID
 * http://stackoverflow.com/questions/151407/how-to-get-an-x11-window-from-a-process-id
 * avoir la derniere fenetre qui poppe XGetInputFocus
 */

class XWindowSystem : public ICommunicationGraphicalServer
{
public:
    XWindowSystem();
    ~XWindowSystem();

    virtual bool getWindows(std::list<Ceg::Window> &);
    virtual bool getFocusedWindow(Ceg::Window & focusedWindow);
    virtual bool setFocusToWindow(Ceg::Window & oldFocusedWindow, Ceg::Window & newFocusedWindow);
    virtual bool refreshWindowInfo(Ceg::Window &);
    virtual bool generateClickEvent(short int buttonID);

private:
    char printIndent(unsigned int) const;
    void printCommands(::Window, unsigned int) const;
    void printWindow(::Window, unsigned int) const;
    void printRecurse(::Window, unsigned int level) const;
    pid_t getPid(::Window) const;
    std::string getPathOfBinary(std::string const & pidStr) const;
    void queryPointer(XEvent&, Window& window, Window& subwindow);

private:
    ::Display* _connection;
};

#endif // XWINDOWSYSTEM_H_
