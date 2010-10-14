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
    // Création et disposition des widgets de la fenêtre
    etatServeur = new QLabel("test");
    boutonQuitter = new QPushButton(tr("Quitter"));
    boutonMsg = new QPushButton(tr("msg"));
    connect(boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    this->connect(boutonMsg, SIGNAL(clicked()), SLOT(sendMsg()));

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(boutonQuitter);
    layout->addWidget(boutonMsg);
    layout->addWidget(etatServeur);
    setLayout(layout);
    setWindowTitle(tr("Test VNC Server"));
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
    std::cerr << "Trying to launch TCP server on port 5900" << std::endl;
    this->_tcpServer = new QTcpServer();
    if (!this->_tcpServer->listen(QHostAddress::Any, 5900))
    {
        std::cerr << "Error: can't listen on port: 5900 " << this->_tcpServer->errorString().toStdString() << std::endl;
    }
    else
    {
        std::cerr << "Ok Listening on port:  5900" << std::endl;
        this->_tcpServer->setMaxPendingConnections(1);
        QObject::connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(_connect()));
    }
}

void	CegTcpServer::_connect()
{
    this->_vncProtocol.init();
    std::cerr << "Connexion d'un client" << std::endl;
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
    std::cerr << "Something to read" << std::endl;
    // Si tout va bien, on continue : on récupère le message
    QDataStream		in(this->_client);

    //in.setVersion(QDataStream::Qt_4_5);
    if (this->_client->bytesAvailable() >= this->_vncProtocol.getWaitedSize())
    {
        std::cout << "Nombre de bytes recus : " << (int)this->_client->bytesAvailable() << std::endl;
        std::cout << "Nombre de bytes attendus par le parseur" << (int)this->_vncProtocol.getWaitedSize() << std::endl;
        this->_vncProtocol.parse(in);
    }
}

void CegTcpServer::send()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    this->_vncProtocol.exec(out);
    std::cout << "CegTcpServer::send()" << std::endl << "Envoie de " << paquet.size() << " octets." << std::endl;
    this->_client->write(paquet);
}

void CegTcpServer::sendMsg()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    this->_vncProtocol.exec(out);
    std::cout << "CegTcpServer::sendMsg()" << std::endl << "Envoie de " << paquet.size()<< " octets." << std::endl;
    this->_client->write(paquet);
}
