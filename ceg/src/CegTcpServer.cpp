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
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
/*********************************/
#include "CegTcpServer.h"
/*********************************/
#include "Singleton.hpp"
#include "MainController.h"
#include "IAction.h"
#include "MoveAction.h"
/*********************************/

CegTcpServer::CegTcpServer() :
  _tcpServer(0), _client(0), _buffer(), _logger(log4cxx::Logger::getLogger("ceg.network"))
{
  //this->launch();
}

CegTcpServer::~CegTcpServer()
{
  std::cout<< "TCP server killed"<< std::endl;
}

void	CegTcpServer::launch(void)
{
  std::cout<< "TCP server launched" << std::endl;
  this->_tcpServer = new QTcpServer();

  if (!this->_tcpServer->listen(QHostAddress::Any, 42000))
    qDebug() << "Netouoooork Error: " /*<< this->_tcpServer->errorString()*/;
  else
    {
      qDebug() << "Network ok, listening on port : 42000";
      this->_tcpServer->setMaxPendingConnections(1);
      QObject::connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(_connect()));
    }
}

void	CegTcpServer::_connect()
{
  this->_client = this->_tcpServer->nextPendingConnection();
  this->connect(this->_client, SIGNAL(readyRead()), SLOT(_readData()));
  this->connect(this->_client, SIGNAL(disconnected()), SLOT(_disconnect()));
}

void	CegTcpServer::_disconnect()
{
  qDebug() << "Disconnected";
}

void	CegTcpServer::_readData()
{
  int			readbytes;
  char			buffer[128];
  QDataStream		in(this->_client);

  //in.setVersion(QDataStream::Qt_4_5);
  while (this->_client->bytesAvailable())
    {
      readbytes = in.readRawData(buffer, sizeof(buffer) - 1);
      if (readbytes > 0)
	{
	  buffer[readbytes] = '\0';
	  this->_buffer.append(buffer);
	}
      else
	return;
    }
  if (this->_buffer.contains('\n'))
    this->parseLines();
}


void	CegTcpServer::parseLines(void)
{
  QStringList cmds = this->_buffer.split('\n', QString::SkipEmptyParts);
  // Interpret each lines.
  for (int i = 0; i < cmds.size(); ++i)
    this->interpretLine(cmds[i]);
  // Remove read lines.
  int last = this->_buffer.lastIndexOf('\n');
  this->_buffer = this->_buffer.remove(0, last + 1);
}

void	CegTcpServer::interpretLine(QString &line)
{
  QTextStream out(stdout);
  MainController	*mc = Singleton<MainController>::getInstance();

  if (mc == NULL)
    {
      out << "Oops critical error, could not get Main Controller instance";
      out << "Oops critical error, command " << line << "can't be executed";
      return ;
    }
  //FIXME convert real rfb numbers into generic actions
  if (line[0] == QChar('a'))
    {
      IAction *ia = new MoveAction(1);
      mc->actionHandler(*ia);
      delete ia;
    }
  if (line[0] == QChar('b'))
    {
      IAction *ia = new MoveAction(1);
      mc->actionHandler(*ia);
      delete ia;
    }

  if (line[0] == QChar('c'))
    {
      //ValidAction
      //IAction *ia = new MoveAction(line[0] - QChar('a'));
      //mc->actionHandler(*ia);
      //delete ia;
    }
}
