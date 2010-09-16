// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyright (C) 2010 CEG development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Authors: CEG <ceg@ionlythink.com>, http://www.ionlythink.com
 */

/*********************************/
#include <iostream>
/*********************************/
#include "CegTcpServer.h"
/*********************************/

CegTcpServer::CegTcpServer() :
  _tcpServer(0), _client(0), _buffer(), tailleMessage(0), _vncProtocol()
{
  //    QObject::connect(this, SIGNAL(actionEmitted(IAction &)),&lm, SLOT(on_action_emitted(IAction&)));
  // Création et disposition des widgets de la fenêtre
  etatServeur = new QLabel();
  boutonQuitter = new QPushButton(tr("Quitter"));
  boutonMsg = new QPushButton(tr("msg"));
  connect(boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
  this->connect(boutonMsg, SIGNAL(clicked()), SLOT(sendMsg()));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(etatServeur);
  layout->addWidget(boutonQuitter);
  layout->addWidget(boutonMsg);
  setLayout(layout);
  setWindowTitle(tr("ZeroChat - Serveur"));
  this->launch();
}

CegTcpServer::~CegTcpServer()
{
    QString msg("TCP server Killed");

    std::cout << (msg.toStdString());

    delete this->_tcpServer;
}

void	CegTcpServer::launch(void)
{
  //    QSettings settings;
  //    QVariant port = settings.value("server/port");
  QString msg;
  QTextStream tmp(&msg);

  tmp << "Trying to launch TCP server on port " << 5900;
  std::cout << (msg.toStdString());
  this->_tcpServer = new QTcpServer();
  msg = "";
  if (!this->_tcpServer->listen(QHostAddress::Any, 5900))
    {
      tmp << "Error: can't listen on port: " << 5900 << " " << this->_tcpServer->errorString();
      this->etatServeur->setText(msg);
    }
  else
    {
      tmp << "Ok Listening on port: " << 5900;
      this->etatServeur->setText(msg);
      this->_tcpServer->setMaxPendingConnections(1);
      QObject::connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(_connect()));
    }
}

void	CegTcpServer::_connect()
{
  this->etatServeur->setText("Connection d'un client !!!");
  this->_client = this->_tcpServer->nextPendingConnection();
  this->connect(this->_client, SIGNAL(readyRead()), SLOT(_readData()));
  this->connect(this->_client, SIGNAL(disconnected()), SLOT(_disconnect()));
}

void	CegTcpServer::_disconnect()
{
  //  this->etatServeur->setText("CegTcpServer: Disconnected");
}

void	CegTcpServer::_readData()
{
    // Si tout va bien, on continue : on récupère le message
    QDataStream		in(this->_client);

    //in.setVersion(QDataStream::Qt_4_5);
    if (this->_client->bytesAvailable() < this->_vncProtocol.getWaitedSize())
    {
        this->_vncProtocol.parse(in);
    }
}

void CegTcpServer::send()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    this->_vncProtocol.exec(out);
    this->_client->write(paquet);
}

void CegTcpServer::sendMsg()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    this->_vncProtocol.exec(out);
    this->_client->write(paquet);
}
