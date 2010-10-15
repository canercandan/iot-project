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
      boost::circular_buffer<char> const &		parse(boost::circular_buffer<char> & bufferToParse);
      boost::circular_buffer<char> const &		execute(Action);
      bool		isInitProcessFinish() const;

    private:
      void		bufcpy(const char *, EBML::uint32);
      void		convertUint8ToString(unsigned char const *, EBML::uint32, std::string &);
      void		parseVersion(boost::circular_buffer<char> &);
      void		parseSecuList(boost::circular_buffer<char> &);
      void		parseSecuResult(boost::circular_buffer<char> &);
      void		parseSecuReason(boost::circular_buffer<char> &);
      void		parseServerInit(boost::circular_buffer<char> &);
      void		execVersion();
      void		execSecuList();
      void		execInitMessage();
      void		execKeyMsg(Action);
      void		execMouseMsg(Action);

    private:
      typedef void (ProtocolClientRFB::*funcParsePtr)(boost::circular_buffer<char> &);

      static std::string const 			_VERSION;
      std::map<RFBServerStep, funcParsePtr>	_parsePtrMap;
      RFBServerStep				_rfbStep;
      char					_secuType;
      char					_sharedFlag;
      unsigned char				_firstSecuResult;
      RFBDesktopInfo				_desktopInfo;
      boost::circular_buffer<char>		_messageToSend;
      unsigned short				_mouseXPosition;
      unsigned short				_mouseYPosition;
      unsigned short				_mouseMoveDistance;
    };
  }
}

#endif //! PROTOCOLCLIENTRFB_H
