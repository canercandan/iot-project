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

#include <iostream>

//#include <QDataStream>
//#include <QString>
//#include <QBool>
#include <Map>

struct VNCPixelFormat {
    unsigned char  bitsPerPixel;
    unsigned char  depth;
    unsigned char  bigEndianFlag;
    unsigned char  trueColourFlag;
    unsigned short redMax;
    unsigned short greenMax;
    unsigned short blueMax;
    unsigned char  redShift;
    unsigned char  greenShift;
    unsigned char  blueShift;
    unsigned char  padding[3];
};

struct VNCDesktopInfo {
  unsigned short	framebufferWidth;
  unsigned short	framebufferHeight;
  VNCPixelFormat	serverPixelFormat;
  unsigned int		nameLength;
  unsigned char		nameString[4];
};

enum VNCServerStep
  {
    VNC_VERSION,
    VNC_SECULIST,
    VNC_SECURESULT,
    VNC_SECUREASON,
    VNC_PASSCHECK,
    VNC_INITMESSAGE,
    VNC_MESSAGING,
    VNC_KEYMSG,
    VNC_PTRMSG
};


enum triBool
{
    TB_UNKNOWN,
    TB_TRUE,
    TB_FALSE
};

class ProtocolServerVNC
{

public:
  typedef void (ProtocolServerVNC::*funcExecPtr)(void *);
  typedef void (ProtocolServerVNC::*funcParsePtr)(void *);

  ProtocolServerVNC();
  ~ProtocolServerVNC();
  void          init();
  void		parse(void * stream);
  void		exec(void * stream);
  VNCServerStep getStep() const;
  int           getWaitedSize() const;

private:
  void          convertStringToUint8(void *, std::string const &);
  void		execVersion(void *);
  void		execSecuList(void *);
  void		execSecuResult(void *);
  void		execSecuReason(void *);
  void		execSand(void *);
  void		execServerInit(void *);
  void		parseVersion(void *);
  void		parseSecuList(void *);
  void		parsePassword(void *);
  void		parseInitMessage(void *);
  void		parseMessage(void *);

private:
  static std::string const			_VERSION;
  QMap<VNCServerStep, funcExecPtr>	_execPtrMap;
  QMap<VNCServerStep, funcParsePtr>	_parsePtrMap;
  VNCServerStep				_vncStep;
  triBool                               _passOk;
  bool					_validSecurity;
  std::string				_secuReason;
  unsigned char				_secuType;
  bool					_validVersion;
};


#endif //! PROTOCOLSERVERVNC_H
