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

#include <iostream>
#include <QDataStream>
#include <QTextStream>
#include "CegTcpServer.h"

//
#include "Singleton.hpp"
#include "Systray.h"

CegTcpServer::CegTcpServer()
{
  this->launch();
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
    std::cerr << "Network Error: " /*<< this->_tcpServer->errorString()*/ << std::endl;
  else
    {
      std::cout<< "Network ok, listening on port : 42000" << std::endl;
      this->_tcpServer->setMaxPendingConnections(1);
      QObject::connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(_connect()));
    }
}

void	CegTcpServer::_connect()
{
  this->_client = this->_tcpServer->nextPendingConnection();
  QObject::connect(this->_client, SIGNAL(readyRead()), this, SLOT(_readData()));
  QObject::connect(this->_client, SIGNAL(disconnected()), this, SLOT(_disconnect()));
}

void	CegTcpServer::_disconnect()
{
  std::cout<< "Disconnected" << std::endl;
}

void	CegTcpServer::_readData()
{
  int			readbytes;
  char			buffer[128];
  QDataStream		in(this->_client);

  in.setVersion(QDataStream::Qt_4_6);
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

void	CegTcpServer::interpretLine(const QString &line)
{
  QTextStream out(stdout);
  Systray* systray;
  systray = Singleton<Systray>::getInstance();
  //systray->lm->;
  if (systray == NULL)
    {
      out << "ooops critical error, could not get systray instance";
      exit(1);
    }
  out << line << endl;

}
