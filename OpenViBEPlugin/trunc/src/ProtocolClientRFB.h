/**
 * \file ProtocolClientRFB.h
 * \author LaChamelle & Jaguar
 * \date 17/10/2010
 * \erief Implementation of the CProtocolClientRFB class
 *
 * This class implement the RFB protocol without 
 * security rules. You can not use the VNC password.
 *
 */

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

    /**
     * \class CProtocolClientRFB
     * \author LaChamelle & Jaguar
     * \date 17/10/2010
     * \erief Implementation of the RFB Protocol
     *
     * This class implement the RFB protocol without 
     * security rules. You can not use the VNC password.
     */
    class CProtocolClientRFB
    {
    public:
      CProtocolClientRFB();
      /**
       * \function initialize
       * \param int32InputMouseMoveDistance[in] : The distance in 
       * pixel which represent the mouse moves
       * \param pInputLogger[in] : Pointer of the logger
       * \erief Initialize two parameters
       *
       * Initialize two parameters
       */

      void						initialize(OpenViBE::int32 int32InputMouseMoveDistance, OpenViBE::Kernel::ILogManager * pInputLogger);

      /**
       * \function parse
       * \param rBufferToParse[in] : it is the buffer received by network
       * \return the buffer to send
       * \erief This method parse the received buffer
       *
       * It choose the correct method which is concerned by the received buffer
       * and parse it.
       */
      boost::circular_buffer<char> const &		parse(boost::circular_buffer<char> & rBufferToParse);

      /**
       * \function execute
       * \param eAction[in] : Represent the action which will be sent
       * \return the buffer to send
       * \erief this method parse the action to send the correct message
       *
       * It choose between the mouse event or keyboard event and create the
       * correct buffer to send
       */
      boost::circular_buffer<char> const &		execute(EAction eAction);

      /**
       * \function isInitProcessFinish
       * \return boolean: true or false
       * \erief Represent if the Initialization process is finished
       *
       * It check if the initialization phase is finished between server 
       * and client if it is finished return true otherwise false
       */
      bool						isInitProcessFinish() const;

    private:
      /**
       * \function bufcpy
       * \param cpSource[in] : source to copy
       * \param uint32Lenght[in] : length to copy
       * \erief Copy the memory to another place
       *
       * Copy source to parameter messageToSend
       */
      void						bufcpy(const char * cpSource, OpenViBE::uint32 uint32Length);

      /**
       * \function convertUint8ToString
       * \param cpData[in] : Data to convert
       * \param uint32Size[in] : Length to convert
       * \param srSrc[out] : Source
       * \erief Convert unsigned int8 bits to String
       *
       * Convert unsigned int8 bits to String
       */
      void						convertUint8ToString(unsigned char const * cpData, OpenViBE::uint32 uint32Size, std::string & srSrc);

      /**
       * \function parseVersion
       * \param rBufferToParse[in] : Buffer to parse
       * \erief Parse the version received by network
       *
       * Parse the version received by network
       */
      void						parseVersion(boost::circular_buffer<char> & rBufferToParse);

      /**
       * \function parseSecuList
       * \param rBufferToParse[in] : Buffer to parse
       * \erief Parse the security list received by network
       *
       * Parse the security list received by network
       */
      void						parseSecuList(boost::circular_buffer<char> & rBufferToParse);

      /**
       * \function parseSecuList
       * \param rBufferToParse[in] : Buffer to parse
       * \erief Parse the security result received by network
       *
       * Parse the security result received by network
       */
      void						parseSecuResult(boost::circular_buffer<char> & rBufferToParse);

      /**
       * \function parseSecuList
       * \param rBufferToParse[in] : Buffer to parse
       * \erief Parse the security reason received by network
       *
       * Parse the security reason received by network
       */
      void						parseSecuReason(boost::circular_buffer<char> & rBufferToParse);

      /**
       * \function parseSecuList
       * \param rBufferToParse[in] : Buffer to parse
       * \erief Parse the server initialisation phase received by network
       *
       * Parse the server initialisation phase received by network
       */
      void						parseServerInit(boost::circular_buffer<char> & rBufferToParse);

      /**
       * \function execVersion
       * \erief Copy the version on the buffer to send
       *
       * Copy the RFB version which is supported by the client
       */
      void						execVersion();

      /**
       * \function execSecuList
       * \erief Choose the supported the security and copy it 
       * in the buffer to send
       *
       * Choose the supported the security and copy it 
       * in the buffer to send
       */
      void						execSecuList();

      /**
       * \function execInitMessage
       * \erief Create the initialization message to send to server
       *
       * Create the initialization message  which will be send to server
       */
      void						execInitMessage();

      /**
       * \function execKeyMsg
       * \param eAction[in] : Keyboard action received by Openvibe
       * \erief Create the keyboard message which will be send to server
       *
       * Create the keyboard message which will be send to server
       */
      void						execKeyMsg(EAction eAction);
 
      /**
       * \function execMouseMsg
       * \param eAction[in] : Mouse action received by Openvibe
       * \erief Create the mouse message which will be send to server
       *
       * Create the mouse message which will be send to server
       */
      void						execMouseMsg(EAction eAction);

    private:
      typedef void (CProtocolClientRFB::*funcParsePtr)(boost::circular_buffer<char> &);

      static std::string const 			m_sVERSION;
      std::map<RFBServerStep, funcParsePtr>	m_oParsePtrMap;
      RFBServerStep				m_oRfbStep;
      char					m_cSecuType;
      char					m_cSharedFlag;
      unsigned char				m_ucFirstSecuResult;
      RFBDesktopInfo				m_oDesktopInfo;
      boost::circular_buffer<char>		m_oMessageToSend;
      unsigned short				m_uint16MouseXPosition;
      unsigned short				m_uint16MouseYPosition;
      unsigned short				m_uint16MouseMoveDistance;
      OpenViBE::Kernel::ILogManager *		m_pLogger;
    };
  }
}

#endif //! PROTOCOLCLIENTRFB_H
