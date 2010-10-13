#ifndef PROTOCOLCLIENTRFB_H
#define PROTOCOLCLIENTRFB_H

#include <map>

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
      void		bufcpy(const unsigned char*, unsigned int);
      void		convertUint8ToString(unsigned char const *, unsigned int, std::string &);
      VncResult		parseVersion(boost::circular_buffer<char> &);
      VncResult		parseSecuList(boost::circular_buffer<char> &);
      VncResult		parseSecuResult(boost::circular_buffer<char> &);
      VncResult		parseSecuReason(boost::circular_buffer<char> &);
      VncResult		parseServerInit(boost::circular_buffer<char> &);
      VncResult		execVersion();
      VncResult		execSecuList();
      VncResult		execInitMessage();
      VncResult		execKeyMsg(Action);
      VncResult		execMouseMsg(Action);

    private:
      typedef std::pair<char*, int> (ProtocolClientRFB::*funcParsePtr)(boost::circular_buffer<char> &);

      static char const *			_VERSION;
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
