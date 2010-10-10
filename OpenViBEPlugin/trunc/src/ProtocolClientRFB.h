#ifndef PROTOCOLCLIENTRFB_H
#define PROTOCOLCLIENTRFB_H

#include <iostream>
#include <map>
#include <utility>

namespace OpenViBEPlugins
{
  namespace VNC
  {
    enum Action //Rajouter ce enum dans le futur .h
    {
      ACTION_MOUSEL = 0, // Mouse Move Left
      ACTION_MOUSER, // Mouse Move Right
      ACTION_MOUSEU, // Mouse Move Up
      ACTION_MOUSED, // Mouse Move Down
      ACTION_MOUSE1, // Mouse Button 1
      ACTION_MOUSE2, // Mouse Button 2
      ACTION_MOUSE3, // Mouse Button 3
      ACTION_KEY1,  // First key
      ACTION_KEY2  // Second key 
    };

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
      typedef std::pair<char*, int> (ProtocolClientRFB::*funcParsePtr)(void *);
      typedef std::pair<char*, int> VncResult;

      ProtocolClientRFB();

      void		bufcpy(void*, void*, int);
      VncResult		parse(void *);
      VncResult		exec(Action);
      RFBServerStep	getStep() const;
      bool		IsInitProcessFinish();
      
    private:
      void	convertUint8ToString(unsigned char *, int, std::string &);
      VncResult	parseVersion(void *);
      VncResult	parseSecuList(void *);
      VncResult	parseSecuResult(void *);
      VncResult	parseSecuReason(void *);
      VncResult	parseServerInit(void *);
      VncResult	execVersion();
      VncResult	execSecuList();
      VncResult	execInitMessage();
      VncResult	execKeyMsg(Action);
      VncResult	execMouseMsg(Action);

    private:
      static char * const			_VERSION;
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
