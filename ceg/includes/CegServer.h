#ifndef CEGSERVER_HPP
#define CEGSERVER_HPP

#include <QtNetwork>

//TODO Singleton


class CegServer : public QObject
{
   Q_OBJECT

   public:
    CegServer();
    ~CegServer();

 private:
    void	_launch();

private slots:
    void	_connect();
    void	_disconnect();
    void	_readData();

 private:
    QTcpServer *_tcpServer;
    QTcpSocket	*_client;
    quint16	_bufLen;
};

#endif // CEGSERVER_HPP
