#ifndef OVP_VNCDEFINE_H_
# define OVP_VNCDEFINE_H_

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

    struct RFBPixelFormat
    {
      unsigned char  bitsPerPixel;
      unsigned char  depth;
      unsigned char  bigEndianFlag;
      unsigned char  trueColourFlag;
      EBML::uint16 redMax;
      EBML::uint16 greenMax;
      EBML::uint16 blueMax;
      unsigned char  redShift;
      unsigned char  greenShift;
      unsigned char  blueShift;
      unsigned char  padding[3];
    };

    struct RFBDesktopInfo
    {
      EBML::uint16	framebufferWidth;
      EBML::uint16	framebufferHeight;
      RFBPixelFormat	serverPixelFormat;
      EBML::uint32		nameLength;
      unsigned char		nameString[4];
    };

    struct RFBKeyEvent
    {
      unsigned char   messageType;
      unsigned char   downFlag;
      unsigned char   padding[2];
      EBML::uint32    key;
    };

    struct RFBPointerEvent
    {
      unsigned char   messageType;
      unsigned char   buttonMask;
      EBML::uint16  xPosition;
      EBML::uint16  yPosition;
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

    typedef std::pair<char*, int> VncResult;
  }
}

#endif // OVP_VNCDEFINE_H_
