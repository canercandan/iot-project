#ifndef PROTOCOLCLIENTRFB_H
#define PROTOCOLCLIENTRFB_H

#include <iostream>
#include <map>
#include <utility>

#include <boost/circular_buffer.hpp>

#include "ovp_vncDefine.h"

namespace OpenViBEPlugins
{
  namespace VNC
  {
    class ProtocolClientRFB
    {
    public:
      ProtocolClientRFB();

      void		initialize(int mouseMoveDistance);
      VncResult		parse(boost::circular_buffer<char> & bufferToParse);
      VncResult		execute(Action);
      bool		isInitProcessFinish() const;

    private:
      void		bufcpy(void*, void*, int);
      RFBServerStep	getStep() const;
      void		convertUint8ToString(unsigned char *, int, std::string &);
      VncResult		parseVersion(void *);
      VncResult		parseSecuList(void *);
      VncResult		parseSecuResult(void *);
      VncResult		parseSecuReason(void *);
      VncResult		parseServerInit(void *);
      VncResult		execVersion();
      VncResult		execSecuList();
      VncResult		execInitMessage();
      VncResult		execKeyMsg(Action);
      VncResult		execMouseMsg(Action);

    private:
      typedef std::pair<char*, int> (ProtocolClientRFB::*funcParsePtr)(void *);

      static char const * 			_VERSION;
      std::map<RFBServerStep, funcParsePtr>	_parsePtrMap;
      RFBServerStep				_rfbStep;
      std::string				_secuReason;
      unsigned char				_secuType;
      unsigned char				_sharedFlag;
      RFBDesktopInfo*				_desktopInfo;
      char					_messageToSend[255];
      unsigned short				_mouseXPosition;
      unsigned short				_mouseYPosition;
      unsigned short				_mouseMoveDistance;
    };
  }
}

#endif //! PROTOCOLCLIENTRFB_H
