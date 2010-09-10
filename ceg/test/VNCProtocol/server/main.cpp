#include <QApplication>

#include "CegTcpServer.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  CegTcpServer * server = new CegTcpServer();

  server->show();

  return app.exec();
}
