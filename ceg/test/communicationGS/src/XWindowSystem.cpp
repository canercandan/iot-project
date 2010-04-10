#include <iostream>
#include <climits>

#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xmu/WinUtil.h>

#include "XWindowSystem.h"

#include <cstdio> /* pour le debug seulement */
#include "TypeToString.hpp"
/* http://tronche.com/gui/x/xlib/ICC/client-to-window-manager/XGetTransientForHint.html
 * // confirm window is a client window
    Window client = XmuClientWindow (displ
 * http://stackoverflow.com/questions/736345/handle-new-top-level-window-events-in-xlib-xt
 *
Top level window on X Window System
Hello,

i want to print on the screen the informations about Top level windows under Linux.

I use the xlib functions. I successfully recurse from the root window to print all the informations about all the element on display.

But i need only the Top-Level window. I don't find any good way to filter.

From wikipedia :

> The top-level windows are exactly the
> direct subwindows of the root window.

With that definition , I have some windows like: gnome-session, seahorse-daemon,notify-osd or icons, on my list and i don't want them.

I also find a function : XmuClientWindow, but i don't understand it's goal.

Thanks to help me.*/

XWindowSystem::XWindowSystem() :
_connection(::XOpenDisplay(0))
{
}

XWindowSystem::~XWindowSystem()
{
    if (this->_connection != 0)
    {
        if (::XCloseDisplay(this->_connection) == BadGC)
        {
            std::cerr << "Scope : XWindowSystem::~XWindowSystem\tFunction : XCloseDisplay fail" << std::endl;
        }
        else
        {
            std::cout << "Connection to Graphical Server close with success." << std::endl;
        }
    }
}

bool XWindowSystem::getWindows(std::list<Ceg::Window> &)
{
    if (this->_connection != 0)
    {
        ::Window rootWindow = ::XDefaultRootWindow(this->_connection);
        this->printRecurse(rootWindow, 0);
    }
    return (this->_connection);
}

bool XWindowSystem::getFocusedWindow(Ceg::Window & /*newWindow*/)
{
    bool statusOp = false;
    if (this->_connection != 0)
    {
        ::Window focusWindow;
        int focusState;
        int status = ::XGetInputFocus(this->_connection, &focusWindow, &focusState);
        if (status != BadValue && status != BadWindow && focusWindow != None)
        {
            std::cout << "window Id" << std::hex << focusWindow << std::dec <<std::endl;
            std::cout << "focus state" << focusState << std::endl;
//            newWindow.setId(focusWindow);
//            statusOp = this->refreshWindowInfo(newWindow);
            this->printWindow(focusWindow, 0);
        }
    }
    return (statusOp);
}

bool XWindowSystem::setFocusToWindow(Ceg::Window & , Ceg::Window & /*newFocusWindow*/)
{
    bool statusOp = false;
    if (this->_connection != 0)
    {
    //int status = ::XSetInputFocus(this->_connection, newFocusWindow, revert_to, time);
    }
    return (statusOp);
}

bool XWindowSystem::refreshWindowInfo(Ceg::Window & targetWindow)
{
    bool statusOp = false;
    if (this->_connection != 0)
    {
        ::XWindowAttributes windowInfos;
        Status status = ::XGetWindowAttributes(this->_connection, targetWindow.getId(), &windowInfos);
        if (status != BadDrawable && status != BadWindow)
        {
            targetWindow.setCharacteristic(WindowGeometry(windowInfos.x, windowInfos.y, windowInfos.width, windowInfos.height));
            statusOp = true;
        }
    }
    return (statusOp);
}

bool XWindowSystem::generateClickEvent(short int, short int)
{
    // click event xlib sur google
    //http://www.linuxquestions.org/questions/programming-9/simulating-a-mouse-click-594576/
    return (true);
}

void XWindowSystem::printRecurse(::Window currentWindow, unsigned int level) const
{
    ::Window rootReturn, parentReturn;
    ::Window * childrenReturn = 0;
    unsigned int nbChildrenReturn = 0;
    Status status = XQueryTree(this->_connection, currentWindow, &rootReturn, &parentReturn, &childrenReturn, &nbChildrenReturn);
    if (status != BadWindow)
    {
        std::cout << this->printIndent(level) << "Window ID : 0x" << std::hex << currentWindow << std::endl;
        std::cout << this->printIndent(level) << "Root : 0x" << rootReturn << std::endl;
        std::cout << this->printIndent(level) << "Parent : 0x" << std::hex << parentReturn << std::dec << std::endl;
        pid_t pid = this->getPid(currentWindow);
        std::cout << this->printIndent(level) << "Pid of the window's creator : " << pid << std::endl;
        if (pid != 0)
        {
            std::cout << this->printIndent(level) << "Binaire utilise : " << this->getPathOfBinary(typeToString(pid)) << std::endl;
        }
        this->printCommands(currentWindow, level);
        this->printWindow(currentWindow, level);
        std::cout << this->printIndent(level) << "Nb child : " << nbChildrenReturn << std::endl;

        ::Window muclient = ::XmuClientWindow(this->_connection, currentWindow);
        std::cout << this->printIndent(level) << "XmuClientWindow : 0x" << muclient << std::endl << std::dec;

        std::cout << std::endl;
        for (unsigned int i = 0; i < nbChildrenReturn; ++i)
        {
            this->printRecurse(childrenReturn[i], level + 1);
        }
        ::XFree(childrenReturn);
    }
    else
    {
        std::cerr << "Scope : XWindowSystem::printRecurse\tFunction XQueryTree fail" << std::endl;
    }
}

pid_t XWindowSystem::getPid(::Window windowId) const
{
    // Un atom est un identifiant unique pour une propriete. d'une fenetre doc http://tronche.com/gui/x/xlib/window-information/properties-and-atoms.html
    Atom atomPid = ::XInternAtom(this->_connection, "_NET_WM_PID", True);
    pid_t pid = 0;
    if (atomPid != BadAlloc && atomPid != BadValue && atomPid != None)
    {
        Atom type;
        int format;
        unsigned long nItems;
        unsigned long bytesAfter;
        unsigned char *propPID = 0;
        if (::XGetWindowProperty(this->_connection, windowId, atomPid, 0, 1, False, XA_CARDINAL, &type, &format, &nItems, &bytesAfter, &propPID) == Success)
        {
            if (propPID != 0)
            {
                pid = *((pid_t *) propPID);
                ::XFree(propPID);
            }
        }
    }
    return (pid);
}

//redhat /exe
std::string XWindowSystem::getPathOfBinary(std::string const & pidStr) const
{
    std::string symbolicLink("/proc/" + pidStr + "/exe");
    char buffer[PATH_MAX];
    ssize_t size = readlink(symbolicLink.c_str(), buffer, PATH_MAX);
    if (size == -1)
    {
	perror("readlink : ");
    }
    else
    {
	buffer[size] = '\0';
        return (buffer);
    }
    return ("");
}

char XWindowSystem::printIndent(unsigned int nbIndent) const
{
    if (nbIndent)
        for (unsigned int i = 0; i < (nbIndent - 1); ++i)
            std::cout << '*';
    return (' ');
}

void XWindowSystem::printWindow(::Window windowId, unsigned int level) const
{
    XTextProperty propWindowName;
    if (::XGetWMName(this->_connection, windowId, &propWindowName) != 0)
    {
        std::cout << this->printIndent(level) << "Window Name : " << propWindowName.value << std::endl;
        ::XFree(propWindowName.value);
    }
    else
    {
        std::cout << "Scope : XWindowSystem::printWindow\tFunction XGetWMName fail" << std::endl;
    }

    XTextProperty propIconName;
    if (::XGetWMIconName(this->_connection, windowId, &propIconName) != 0)
    {
        if (propIconName.value != 0)
        {
            std::cout << this->printIndent(level) << "Icon Name : " << propIconName.value << std::endl;
            ::XFree(propIconName.value);
        }
    }

    XClassHint classHintsReturn;
    Status status = ::XGetClassHint(this->_connection, windowId, &classHintsReturn);
    if (status != 0 && status != BadWindow)
    {
        if (classHintsReturn.res_name)
        {
            std::cout << this->printIndent(level) << "Application Name : " << classHintsReturn.res_name << std::endl;
            ::XFree(classHintsReturn.res_name);
        }
        if (classHintsReturn.res_class)
        {
            std::cout << this->printIndent(level) << "Application Class : " << classHintsReturn.res_class << std::endl;
            ::XFree(classHintsReturn.res_class);
        }
    }
    else
    {
        std::cout << "Scope : XWindowSystem::printWindow\tFunction XGetClassHint fail" << std::endl;
    }

    ::XWindowAttributes windowInfos;
    status = ::XGetWindowAttributes(this->_connection, windowId, &windowInfos);
    if (status != BadDrawable && status != BadWindow)
    {

        std::cout << this->printIndent(level) << "x : " << windowInfos.x << std::endl;
        std::cout << this->printIndent(level) << "y : " << windowInfos.y << std::endl;
        // cf function Display_Stats_Info for absolute window
        std::cout << this->printIndent(level) << "width : " << windowInfos.width << std::endl;
        std::cout << this->printIndent(level) << "height : " << windowInfos.height << std::endl;
        std::cout << this->printIndent(level) << "Visible : " << ((windowInfos.map_state == IsUnmapped) ? "IsUnmapped" : (windowInfos.map_state == IsUnviewable) ? "IsUnviewable" : "IsViewable") << std::endl;
    }
    else
    {
        std::cout << "Scope : XWindowSystem::printWindow\tFunction XGetWindowAttributes fail" << std::endl;
    }
}

void XWindowSystem::printCommands(::Window windowId, unsigned int level) const
{
    int argcReturn;
    char **argvReturn;
    Status status = ::XGetCommand(this->_connection, windowId, &argvReturn, &argcReturn);
    if (status != 0)
    {
        std::cout << this->printIndent(level) << "argc : " << argcReturn << std::endl;
        std::cout << this->printIndent(level) << "argv :";
        for (int i = 0; i < argcReturn; ++i)
        {
            std::cout << ' ' << argvReturn[i];
        }
        std::cout << std::endl;
        ::XFreeStringList(argvReturn);
    }
    else
    {
        std::cout << "Scope : XWindowSystem::printCommands\tFunction XGetCommand fail" << std::endl;
    }
}
