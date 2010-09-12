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

struct VNCPixelFormat {
    quint8  bitsPerPixel;
    quint8  depth;
    quint8  bigEndianFlag;
    quint8  trueColourFlag;
    quint16 redMax;
    quint16 greenMax;
    quint16 blueMax;
    quint8  redShift;
    quint8  greenShift;
    quint8  blueShift;
    quint8  padding[3];
};

struct VNCDesktopInfo {
    quint16         framebufferWidth;
    quint16         framebufferHeight;
    VNCPixelFormat  serverPixelFormat;
    quint32         nameLength;
    quint8*         nameString;
};

enum VNCServerStep
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
  typedef void (protocoleYAY::*funcParsePtr)(QDataStream &, QString &);

  ProtocolServerVNC();
  ~ProtocolServerVNC();
  void          init();
  QString	parse(QDataStream & stream);
  QString	exec();
  VNCServerStep getStep() const;

private:
  void          convertStringToUint8(QDataStream &, QString const &);
  void		execVersion(QDataStream &);
  void		execSecuList(QDataStream &);
  void		execSecuResult(QDataStream &);
  void		execSecuReason(QDataStream &);
  void		execSand(QDataStream &);
  void		execServerInit(QDataStream &);
  void		parseVersion(QDataStream &, QString &);
  void		parseSecuList(QDataStream &, QString &);
  void		parseSecuFail(QDataStream &, QString &);
  void		parsePassword(QDataStream &, QString &);
  void		parseInitMessage(QDataStream &, QString &);
  void		parseMessage(QDataStream &, QString &);

private:
  static QString const                  _VERSION;
  QMap<VNCServerStep, funcExecPtr>	_execPtrMap;
  QMap<VNCServerStep, funcParsePtr>	_parsePtrMap;
  VNCServerStep				_vncStep;
  triBool                               _passOk;
  QBool                                 _validSecurity;
  QString                               _secuReason;
  quint8                                _secuType;
};


#endif //! PROTOCOLSERVERVNC_H
