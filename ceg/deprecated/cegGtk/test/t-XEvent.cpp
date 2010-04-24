#include <X11/Xlib.h>
#include <cstdio>

int main()
{
  Display *display;
  Window rootwin;

  display = XOpenDisplay( NULL );
  rootwin = DefaultRootWindow( display );
  XSelectInput( display, rootwin, SubstructureNotifyMask );

  XEvent event;

  while ( 1 ) {
    XNextEvent( display, &event );
    if ( event.type == MapNotify ) {
      XMapEvent *mapevent = (XMapEvent *)&event;
      printf( "Mapped    : 0x%x\n", (unsigned int)(mapevent->window) );
    }
    if ( event.type == DestroyNotify ) {
      XDestroyWindowEvent *destroywindowevent = (XDestroyWindowEvent *)&event;
      printf( "Destroyed : 0x%x\n", (unsigned int)(destroywindowevent->window) );
    }
    if ( event.type == ReparentNotify ) {
      XReparentEvent *reparentevent = (XReparentEvent *)&event;
      printf( "Reparented: 0x%x to 0x%x\n", (unsigned int)(reparentevent->window), (unsigned int)(reparentevent->parent) );
    }
  }

  return 0;
}
