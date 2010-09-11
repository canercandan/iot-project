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
#ifndef PROTOCOLSERVERVNC_H
#define PROTOCOLSERVERVNC_H

#include <QDataStream>
#include <QString>
#include <QBool>
#include <QMap>


enum vncServerStep
  {
    VNC_VERSION,
    VNC_SECULIST,
    VNC_SECUFAIL,
    VNC_SECURESULT,
    VNC_SECUREASON,
    VNC_PASSCHECK,
    VNC_INITMESSAGE,
    VNC_MESSAGING};


enum triBool
{
    TB_UNKNOWN,
    TB_TRUE,
    TB_FALSE
};

class ProtocolServerVNC
{

public:
  typedef void (protocoleYAY::*funcExecPtr)(QDataStream &);
  typedef void (protocoleYAY::*funcParsePtr)(char *, QString &);

  ProtocolServerVNC();
  ~ProtocolServerVNC();
  void          init();
  QString	parse(char *);
  QString	exec();

private:
  void		execVersion(QDataStream &);
  void		execSecuList(QDataStream &);
  void		execSecuResult(QDataStream &);
  void		execSecuReason(QDataStream &);
  void		execSand(QDataStream &);
  void		execServerInit(QDataStream &);
  void		parseVersion(char *, QString &);
  void		parseSecuList(char *, QString &);
  void		parseSecuFail(char *, QString &);
  void		parsePassword(char *, QString &);
  void		parseInitMessage(char *, QString &);

private:
  QMap<vncServerStep, funcExecPtr>	_execPtrMap;
  QMap<vncServerStep, funcParsePtr>	_parsePtrMap;
  vncServerStep				_vncStep;
  triBool                               _passOk;
};


#endif //! PROTOCOLSERVERVNC_H
