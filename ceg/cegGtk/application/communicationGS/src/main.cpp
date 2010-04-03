#include <iostream>
#include <cstdlib>

#ifdef _WIN32

#include "Win32Explorer.h"

int main(int argc, char *argv[], char *envp[])
{
    ICommunicationGraphicalServer * comGS = new Win32Explorer();
    std::list<Ceg::Window> windows;
    std::cout << "Top Level Windows: " << std::endl;
    comGS->getWindows(windows);
    Ceg::Window temp;
    comGS->getFocusedWindow(temp);

    delete comGS;
    return (EXIT_SUCCESS);
}

#else

#include "XWindowSystem.h"


int main()
{
    ICommunicationGraphicalServer * comGS = new XWindowSystem();
    std::list<Ceg::Window> windows;
    std::cout << "Top Level Windows: " << std::endl;
    comGS->getWindows(windows);
//    Ceg::Window temp;
//    comGS->getFocusedWindow(temp);342946d

    delete comGS;
    return (EXIT_SUCCESS);
}

#endif
