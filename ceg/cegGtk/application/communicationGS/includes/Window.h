#ifndef WINDOW_H_
#define WINDOW_H_

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>		// NT only!
#pragma comment(lib, "psapi")	// NT only!
#else
#include <X11/Xlib.h>
#endif
#include "WindowGeometry.h"

namespace Ceg
{
#ifdef _WIN32
    typedef ::HWND WindowId;
#else
    typedef ::Window WindowId;
#endif

    class Window
    {
    public:
        Window();
        Window(WindowId, WindowGeometry const &, bool = false);

        WindowId getId() const;
        void setId(WindowId);
        void setCharacteristic(WindowGeometry const &);

    private:
        WindowId _id;
        WindowGeometry _characteristic;
        bool _isVisible;
    };
}

#endif // WINDOW_H_
