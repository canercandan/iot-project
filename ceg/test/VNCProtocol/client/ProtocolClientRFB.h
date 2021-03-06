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
#ifndef PROTOCOLCLIENTRFB_H
#define PROTOCOLCLIENTRFB_H

#include <iostream>

#include <map>

struct RFBPixelFormat {
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

struct RFBDesktopInfo
{
  unsigned short	framebufferWidth;
  unsigned short	framebufferHeight;
  RFBPixelFormat	serverPixelFormat;
  unsigned int		nameLength;
  unsigned char		nameString[4];
};

struct RFBKeyEvent
{
    unsigned char   messageType;
    unsigned char   downFlag;
    unsigned char   padding[2];
    unsigned int    key;
};

struct RFBPointerEvent
{
    unsigned char   messageType;
    unsigned char   bouttonMask;
    unsigned short  xPosition;
    unsigned short  yPosition;
};


enum RFBMessageTypes
{
    RFB_SETPIXELFORMAT = 0,
    RFB_SETENCONDINGS = 2,
    RFB_FRAMEBUFFERUPDATEREQUEST = 3,
    RFB_KEYEVENT = 4,
    RFB_POINTEREVENT = 5,
    RFB_CLIENTCUTTEXT = 6
};

enum RFBServerStep
  {
    RFB_VERSION,
    RFB_SECULIST,
    RFB_SECURESULT,
    RFB_SECUREASON,
    RFB_PASSCHECK,
    RFB_INITMESSAGE,
    RFB_MESSAGING,
    RFB_KEYMSG,
    RFB_PTRMSG,
    RFB_DISCONNECT
};


enum triBool
{
    TB_UNKNOWN,
    TB_TRUE,
    TB_FALSE
};

class ProtocolClientRFB
{

public:
  typedef void (ProtocolClientRFB::*funcExecPtr)();
  typedef void (ProtocolClientRFB::*funcParsePtr)(void *);

  ProtocolClientRFB();
  ~ProtocolClientRFB();
  void          init();
  void		parse(void * stream);
  void		exec();
  RFBServerStep getStep() const;
  int           getWaitedSize() const;

private:
  void          convertUint8ToString(unsigned char *, int, std::string &);
  void		parseVersion(void *);
  void		parseSecuList(void *);
  void		parseSecuResult(void *);
  void		parseSecuReason(void *);
  void		parseServerInit(void *);
  void		execVersion();
  void		execSecuList();
  void		execInitMessage();
  void		execMessage();

private:
  static char * const           	_VERSION;
  std::map<RFBServerStep, funcExecPtr>	_execPtrMap;
  std::map<RFBServerStep, funcParsePtr>	_parsePtrMap;
  RFBServerStep				_rfbStep;
  std::string				_secuReason;
  unsigned char				_secuType;
  unsigned char                         _sharedFlag;
  RFBDesktopInfo*                       _desktopInfo;
  void*                                 _messageToSend;
  unsigned short                        _mouseXPosition;
  unsigned short                        _mouseYPosition;
};


#endif //! PROTOCOLCLIENTRFB_H
