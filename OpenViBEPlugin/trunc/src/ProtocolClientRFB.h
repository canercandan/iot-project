#ifndef PROTOCOLCLIENTRFB_H
#define PROTOCOLCLIENTRFB_H

#include <map>

#include <boost/circular_buffer.hpp>

#include <openvibe-toolkit/ovtk_all.h>

#include "ovp_vncDefine.h"

namespace OpenViBEPlugins
{
  namespace VNC
  {
    class ProtocolClientRFB
    {
    public:
      ProtocolClientRFB();

      void		initialize(EBML::int32 mouseMoveDistance);
      VncResult		parse(boost::circular_buffer<char> & bufferToParse);
      VncResult		execute(Action);
      bool		isInitProcessFinish() const;

    private:
      void		bufcpy(const char *, EBML::uint32);
      void		convertUint8ToString(unsigned char const *, EBML::uint32, std::string &);
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
      typedef std::pair<char*, EBML::int32> (ProtocolClientRFB::*funcParsePtr)(boost::circular_buffer<char> &);

      static std::string const 			_VERSION;
      std::map<RFBServerStep, funcParsePtr>	_parsePtrMap;
      RFBServerStep				_rfbStep;
      std::string				_secuReason;
      char					_secuType;
      char					_sharedFlag;
      unsigned char				_firstSecuResult;
      RFBDesktopInfo				_desktopInfo;
      char					_messageToSend[255];
      unsigned short				_mouseXPosition;
      unsigned short				_mouseYPosition;
      unsigned short				_mouseMoveDistance;
    };
  }
}

#endif //! PROTOCOLCLIENTRFB_H
