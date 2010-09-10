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
  _tcpServer(0), _client(0), _buffer(), tailleMessage(0)
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
  //this->send("");
  this->send("RFB 003.008\n");
}

void	CegTcpServer::_disconnect()
{
  //  this->etatServeur->setText("CegTcpServer: Disconnected");
}

void	CegTcpServer::_readData()
{
    // Si tout va bien, on continue : on récupère le message
    int			readbytes;
    char			buffer[128];
    QByteArray          buff;
    QDataStream		in(this->_client);

    //in.setVersion(QDataStream::Qt_4_5);
    while (this->_client->bytesAvailable())
    {
        in >> buff;
            /*        readbytes = in.readRawData(buffer, sizeof(buffer) - 1);
        if (readbytes > 0)
        {
            buffer[readbytes] = '\0';
            this->etatServeur->setText(buffer);
        }
        else
            return;*/
        this->etatServeur->setText(buff);
    }
}

/*
void	readData()
{
  // 1 : on reçoit un paquet (ou un sous-paquet) d'un des clients

  // On détermine quel client envoie le message (recherche du QTcpSocket du client)
  QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
  if (socket == 0) // Si par hasard on n'a pas trouvé le client �  l'origine du signal, on arrête la méthode
    return;

  // Si tout va bien, on continue : on récupère le message
  QDataStream in(socket);

  if (tailleMessage == 0) // Si on ne connaît pas encore la taille du message, on essaie de la récupérer
    {
      if (socket->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas reçu la taille du message en entier
	return;

      in >> tailleMessage; // Si on a reçu la taille du message en entier, on la récupère
    }

  // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
  if (socket->bytesAvailable() < tailleMessage) // Si on n'a pas encore tout reçu, on arrête la méthode
    return;


  // Si ces lignes s'exécutent, c'est qu'on a reçu tout le message : on peut le récupérer !
  QString message;
  in >> message;


  // 3 : remise de la taille du message �  0 pour permettre la réception des futurs messages
  tailleMessage = 0;
}
*/

void CegTcpServer::send(const QString &message)
{
  // Préparation du paquet
  QByteArray paquet;

  //out << (quint16) 0;
  paquet += "RFB 003.008\n";
  //out << "RFB 003.008\n"; // On ajoute le message �  la suite
  //out.device()->seek(0); // On se replace au début du paquet
  //out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message


  // Envoi du paquet préparé �  tous les clients connectés au serveur
  this->_client->write(paquet);
}

void CegTcpServer::sendMsg()
{
  // Préparation du paquet
  QByteArray paquet;
  QDataStream out(&paquet, QIODevice::WriteOnly);

  //out << (quint16) 0;
  QString message;
  out << message; // On ajoute le message �  la suite
  //out.device()->seek(0); // On se replace au début du paquet
  //out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message


  // Envoi du paquet préparé �  tous les clients connectés au serveur
  this->_client->write(paquet);
}


void	CegTcpServer::parseLines(void)
{
  //QStringList cmds = this->_buffer.split('\n', QString::SkipEmptyParts);
    // Interpret each lines.
    //for (int i = 0; i < cmds.size(); ++i)
  //	this->interpretLine(cmds[i]);
    // Remove read lines.
    //int last = this->_buffer.lastIndexOf('\n');
    //this->_buffer = this->_buffer.remove(0, last + 1);
}

void	CegTcpServer::interpretLine(QString &/*line*/)
{
    //QTextStream		out(stdout);

    //FIXME convert real rfb numbers into generic actions
  // QString ia;
    //    if (line[0] == QChar('a'))
    //    {
    //        ia = new MoveAction(Qt::Key_Left);
    //    }
    //    if (line[0] == QChar('b'))
    //    {
    //        ia = new MoveAction(Qt::Key_Up);
    //    }
    //    if (line[0] == QChar('c'))
    //    {
    //        ia = new ValidAction();
    //    }
  // emit actionEmitted();
}
