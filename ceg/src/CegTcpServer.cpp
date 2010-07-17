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
#include <QSettings>
/*********************************/
#include "CegTcpServer.h"
/*********************************/
#include "MainController.h"
#include "IAction.h"
#include "MoveAction.h"
#include "ValidAction.h"
#include "ActionFactory.h"
/*********************************/

CegTcpServer::CegTcpServer(MainController& lm) :
        _tcpServer(0), _client(0), _buffer()
#ifndef Q_WS_WIN
        , _logger(log4cxx::Logger::getLogger("ceg.network"))
#endif
{
    QObject::connect(this, SIGNAL(actionEmitted(IAction &)),&lm, SLOT(onActionEmitted(IAction&)));
    this->launch();
}

CegTcpServer::~CegTcpServer()
{
#ifndef Q_WS_WIN
    LOG4CXX_INFO(this->_logger, "TCP server killed");
#endif
}

void	CegTcpServer::launch(void)
{
    QSettings settings;
    QVariant port = settings.value("server/port");

#ifndef Q_WS_WIN
    LOG4CXX_INFO(this->_logger, "TCP server launched on port " << port.toInt());
#endif

    this->_tcpServer = new QTcpServer();

    if (!this->_tcpServer->listen(QHostAddress::Any, port.toInt()))
    {
#ifndef Q_WS_WIN
        LOG4CXX_ERROR(this->_logger, "Error: can't listen on port: " << port.toInt());
        LOG4CXX_ERROR(this->_logger, this->_tcpServer->errorString().toStdString());
#endif
    }
    else
    {
#ifndef Q_WS_WIN
        LOG4CXX_INFO(this->_logger, "Listening on port: " << port.toInt());
#endif

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
#ifndef Q_WS_WIN
    LOG4CXX_INFO(this->_logger,"Disconnected");
#endif
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

void	CegTcpServer::interpretLine(QString &/*line*/)
{
    QTextStream		out(stdout);

    //FIXME convert real rfb numbers into generic actions
    IAction *ia = 0;
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
    emit actionEmitted(*ia);
    delete ia;
}
