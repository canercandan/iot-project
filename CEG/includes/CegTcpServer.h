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

#ifndef CEGTCPSERVER_HPP
#define CEGTCPSERVER_HPP

#include <QObject>
#include <QString>

class QTcpServer;
class QTcpSocket;

class CegTcpServer : public QObject
{
  Q_OBJECT

  public:
  CegTcpServer();
  ~CegTcpServer();

private:
  void	launch();
  void	parseLines(void);
  void	interpretLine(QString &line);

private slots:
  void	_connect();
  void	_disconnect();
  void	_readData();

private:
  QTcpServer	*_tcpServer;
  QTcpSocket	*_client;
  QString	_buffer;
};

#endif // CEGTCPSERVER_HPP
