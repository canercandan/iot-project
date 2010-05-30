#include <iostream>
#include <QDataStream>

#include "CegServer.h"


CegServer::CegServer()
{
  this->_launch();
}

CegServer::~CegServer()
{
  std::cout<< "TCP server killed"<< std::endl;
}

void	CegServer::_launch(void)
{
  std::cout<< "TCP server launched" << std::endl;
  this->_tcpServer = new QTcpServer();

  if (!this->_tcpServer->listen(QHostAddress::Any, 42000))
  {
      // Fail
      std::cerr << "Network Error: " /*<< this->_tcpServer->errorString()*/ << std::endl;

  }
  else
    {
      // OK
      std::cout<< "Network ok, listening on port : 42000" << std::endl;
      this->_tcpServer->setMaxPendingConnections(1);
      QObject::connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(_connect()));

    }

}


void	CegServer::_connect()
{
  this->_client = this->_tcpServer->nextPendingConnection();

  QObject::connect(this->_client, SIGNAL(readyRead()), this, SLOT(_readData()));
  QObject::connect(this->_client, SIGNAL(disconnected()), this, SLOT(_disconnect()));
}


void	CegServer::_disconnect()
{
}

void	CegServer::_readData()
{
std::cout << "Message recu" << std::endl;
    // Si tout va bien, on continue : on récupère le message
  QDataStream in(this->_client);
 // Si on ne connaît pas encore la taille du message, on essaie de la récupérer
if (this->_msgLen == 0)
  {
    if (this->_client->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas reçu la taille du message en entier
      return;
    in >> this->_msgLen; // Si on a reçu la taille du message en entier, on la récupère
  }
// Si on connaît la taille du message, on vérifie si on a reçu le message en entier
if (this->_client->bytesAvailable() < this->_msgLen) // Si on n'a pas encore tout reçu, on arrête la méthode
  return;
// Si ces lignes s'exécutent, c'est qu'on a reçu tout le message : on peut le récupérer !
QString message;
in >> message;
std::cout << "tout recu!!" << std::endl;
std::cout<< this->_msgLen << std::endl;
// 3 : remise de la taille du message à 0 pour permettre la réception des futurs messages
this->_msgLen = 0;
}

