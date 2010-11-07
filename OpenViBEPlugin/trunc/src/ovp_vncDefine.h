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

    struct SRFBPixelFormat
    {
      unsigned char	m_ucBitsPerPixel;
      unsigned char	m_ucDepth;
      unsigned char	m_ucBigEndianFlag;
      unsigned char	m_ucTrueColourFlag;
      OpenViBE::uint16	m_uint16RedMax;
      OpenViBE::uint16	m_uint16GreenMax;
      OpenViBE::uint16	m_uintBlueMax;
      unsigned char	m_ucRedShift;
      unsigned char	m_ucGreenShift;
      unsigned char	m_ucBlueShift;
      unsigned char	m_ucPadding[3];
    };

    struct SRFBDesktopInfo
    {
      OpenViBE::uint16	m_uint16FramebufferWidth;
      OpenViBE::uint16	m_uint16FramebufferHeight;
      SRFBPixelFormat	m_oServerPixelFormat;
      OpenViBE::uint32	m_uint32NameLength;
      unsigned char	m_cNameString[4];
    };

    struct SRFBKeyEvent
    {
      unsigned char	m_ucMessageType;
      unsigned char	m_ucDownFlag;
      unsigned char	m_ucPadding[2];
      OpenViBE::uint32	m_uint32Key;
    };

    struct SRFBPointerEvent
    {
      unsigned char	m_ucMessageType;
      unsigned char	m_ucButtonMask;
      OpenViBE::uint16	m_uint16XPosition;
      OpenViBE::uint16	m_uint16YPosition;
    };

    enum ERFBServerStep
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
  }
}

#endif // OVP_VNCDEFINE_H_
