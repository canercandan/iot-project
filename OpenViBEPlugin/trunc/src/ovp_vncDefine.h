#ifndef OVP_VNCDEFINE_H_
# define OVP_VNCDEFINE_H_

namespace OpenViBEPlugins
{
  namespace VNC
  {
    /**
     * \brief Vnc action available
     */
    enum EAction
    {
      ACTION_MOUSEL = 0, /**< Mouse Move Left */
      ACTION_MOUSER, /**< Mouse Move Right */
      ACTION_MOUSEU, /**< Mouse Move Up */
      ACTION_MOUSED, /**< Mouse Move Down */
      ACTION_MOUSE1, /**< Mouse Button 1 */
      ACTION_MOUSE2, /**< Mouse Button 2 */
      ACTION_MOUSE3, /**< Mouse Button 3 */
      ACTION_KEY1,  /**< First key */
      ACTION_KEY2  /**< Second key */
    };

    struct RFBPixelFormat
    {
      unsigned char	bitsPerPixel;
      unsigned char	depth;
      unsigned char	bigEndianFlag;
      unsigned char	trueColourFlag;
      OpenViBE::uint16	redMax;
      OpenViBE::uint16	greenMax;
      OpenViBE::uint16	blueMax;
      unsigned char	redShift;
      unsigned char	greenShift;
      unsigned char	blueShift;
      unsigned char	padding[3];
    };

    struct RFBDesktopInfo
    {
      OpenViBE::uint16	framebufferWidth;
      OpenViBE::uint16	framebufferHeight;
      RFBPixelFormat	serverPixelFormat;
      OpenViBE::uint32	nameLength;
      unsigned char	nameString[4];
    };

    struct RFBKeyEvent
    {
      unsigned char	messageType;
      unsigned char	downFlag;
      unsigned char	padding[2];
      OpenViBE::uint32	key;
    };

    struct RFBPointerEvent
    {
      unsigned char	messageType;
      unsigned char	buttonMask;
      OpenViBE::uint16	xPosition;
      OpenViBE::uint16	yPosition;
    };

    /* enum ERFBMessageTypes */
    /* { */
    /*   RFB_SETPIXELFORMAT = 0, */
    /*   RFB_SETENCONDINGS = 2, */
    /*   RFB_FRAMEBUFFERUPDATEREQUEST = 3, */
    /*   RFB_KEYEVENT = 4, */
    /*   RFB_POINTEREVENT = 5, */
    /*   RFB_CLIENTCUTTEXT = 6 */
    /* }; */

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

    /* enum ETriBool */
    /* { */
    /*   TB_UNKNOWN, */
    /*   TB_TRUE, */
    /*   TB_FALSE */
    /* }; */
  }
}

#endif // OVP_VNCDEFINE_H_
