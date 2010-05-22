#include <QtGui>
#include "systray.h"

int	main(int argc, char *argv[])
{
  QApplication	app(argc, argv);

  if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
      QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("Couldn't detect any system tray on this system."));
      return 1;
    }

  Systray window;
  window.show();
  return app.exec();
}
