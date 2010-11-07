#include <iostream> // Remove une fois le debug termine

#include "ProtocolClientRFB.h"

using namespace OpenViBEPlugins::VNC;

std::string const CProtocolClientRFB::m_sVERSION = std::string("RFB 003.008\n");

CProtocolClientRFB::CProtocolClientRFB():
  m_oParsePtrMap(), m_oRfbStep(RFB_VERSION),
  m_cSecuType(0), m_cSharedFlag(0), m_ucFirstSecuResult(1), m_oMessageToSend(256),
  m_uint16MouseXPosition(0), m_uint16MouseYPosition(0), m_uint16MouseMoveDistance(5), m_pLogger(0)
{
  this->m_oParsePtrMap[RFB_VERSION] = &CProtocolClientRFB::parseVersion;
  this->m_oParsePtrMap[RFB_SECULIST] = &CProtocolClientRFB::parseSecuList;
  this->m_oParsePtrMap[RFB_SECURESULT] = &CProtocolClientRFB::parseSecuResult;
  this->m_oParsePtrMap[RFB_SECUREASON] = &CProtocolClientRFB::parseSecuReason;
  this->m_oParsePtrMap[RFB_INITMESSAGE] = &CProtocolClientRFB::parseServerInit;
  this->m_oRfbStep = RFB_VERSION;
}

void		CProtocolClientRFB::initialize(OpenViBE::int32 int32InputMouseMoveDistance, OpenViBE::Kernel::ILogManager * pInputLogger)
{
  this->m_uint16MouseMoveDistance = int32InputMouseMoveDistance;
  this->m_pLogger = pInputLogger;
}

bool		CProtocolClientRFB::isInitProcessFinish() const
{
  return (RFB_MESSAGING == this->m_oRfbStep);
}

void	CProtocolClientRFB::bufcpy(const char * source, OpenViBE::uint32 length)
{
  this->m_oMessageToSend.insert(this->m_oMessageToSend.end(), source, source + length);
}

void	CProtocolClientRFB::convertUint8ToString(unsigned char const * data, OpenViBE::uint32 size, std::string & src)
{
  std::copy(data, data + size, src.begin());
}

void	CProtocolClientRFB::execVersion()
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::execVersion] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  this->bufcpy(CProtocolClientRFB::m_sVERSION.c_str(), CProtocolClientRFB::m_sVERSION.size());
  this->m_oRfbStep = RFB_SECULIST;
}

void		CProtocolClientRFB::execSecuList()
{
std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::execSecuList] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  this->bufcpy(&this->m_cSecuType, 1);
  this->m_oRfbStep = RFB_SECURESULT;
}

void		CProtocolClientRFB::execInitMessage()
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::execInitMessage] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  this->bufcpy(&this->m_cSharedFlag, 1);
}

void		CProtocolClientRFB::execKeyMsg(EAction eAction)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::execKeyMsg] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  SRFBKeyEvent	l_oKeyEvent;
  l_oKeyEvent.m_ucMessageType = 4;
  l_oKeyEvent.m_ucDownFlag = 1;
  l_oKeyEvent.m_uint32Key = (eAction == ACTION_KEY1 ? 'A' : 'B');//0x0041 : 0x0042); // Correspond a A et B

  this->bufcpy((char*)&l_oKeyEvent, sizeof(SRFBKeyEvent));
  l_oKeyEvent.m_ucDownFlag = 0;
  this->bufcpy((char*)&l_oKeyEvent, sizeof(SRFBKeyEvent));
}

void		CProtocolClientRFB::execMouseMsg(EAction eAction)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::execMouseMsg] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cerr << "Distance de deplacement = " << this->m_uint16MouseMoveDistance << std::endl;
  std::cerr << "Taille du desktop width = "<< m_oDesktopInfo.m_uint16FramebufferWidth << " Height = "<< m_oDesktopInfo.m_uint16FramebufferHeight << std::endl;
  std::cerr << "Avant Position du pointeur x = " << this->m_uint16MouseXPosition << " - y = " << this->m_uint16MouseYPosition << std::endl;
  SRFBPointerEvent	l_oPointerEvent;
  l_oPointerEvent.m_ucMessageType = 5;
  l_oPointerEvent.m_ucButtonMask = 0;
  switch (eAction)
    {
    case ACTION_MOUSEL:
      if ((this->m_uint16MouseXPosition - this->m_uint16MouseMoveDistance) <= 0)
	this->m_uint16MouseXPosition = this->m_oDesktopInfo.m_uint16FramebufferWidth;
      else
	this->m_uint16MouseXPosition -= this->m_uint16MouseMoveDistance;
      break;

    case ACTION_MOUSER:
      if ((this->m_uint16MouseXPosition + this->m_uint16MouseMoveDistance) > this->m_oDesktopInfo.m_uint16FramebufferWidth)
	this->m_uint16MouseXPosition = 0;
      else
	this->m_uint16MouseXPosition += this->m_uint16MouseMoveDistance;
      break;

    case ACTION_MOUSEU:
      if ((this->m_uint16MouseYPosition - this->m_uint16MouseMoveDistance) <= 0)
	this->m_uint16MouseYPosition = this->m_oDesktopInfo.m_uint16FramebufferHeight;
      else
	this->m_uint16MouseYPosition -= this->m_uint16MouseMoveDistance;
      break;

    case ACTION_MOUSED:
      if ((this->m_uint16MouseYPosition + this->m_uint16MouseMoveDistance) > this->m_oDesktopInfo.m_uint16FramebufferHeight)
	this->m_uint16MouseYPosition = 0;
      else
	this->m_uint16MouseYPosition += this->m_uint16MouseMoveDistance;
      break;

    case ACTION_MOUSE1:
      l_oPointerEvent.m_ucButtonMask = 1;
      break;

    case ACTION_MOUSE2:
      l_oPointerEvent.m_ucButtonMask = 1 << 1;
      break;

    case ACTION_MOUSE3:
      l_oPointerEvent.m_ucButtonMask = 1 << 2;
      break;
    default:
      break;
    }
  std::cerr << "Apres Position du pointeur x = " << this->m_uint16MouseXPosition << " - y = " << this->m_uint16MouseYPosition << std::endl;
  l_oPointerEvent.m_uint16XPosition = this->m_uint16MouseXPosition;
  l_oPointerEvent.m_uint16YPosition = this->m_uint16MouseYPosition;
  this->bufcpy((char*)&l_oPointerEvent, sizeof(SRFBPointerEvent));
  l_oPointerEvent.m_ucButtonMask = 0;
  this->bufcpy((char*)&l_oPointerEvent, sizeof(SRFBPointerEvent));
}

boost::circular_buffer<char> const &	CProtocolClientRFB::execute(EAction eAction)
{
  this->m_oMessageToSend.clear();
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::execute] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (eAction >= ACTION_KEY1)
    {
      this->execKeyMsg(eAction);
    }
  else
    {
      this->execMouseMsg(eAction);
    }
  return (this->m_oMessageToSend);
}

void		CProtocolClientRFB::parseVersion(boost::circular_buffer<char> & rBufferToParse)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::parseVersion] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (rBufferToParse.size() >= CProtocolClientRFB::m_sVERSION.size())
    {
      rBufferToParse.erase_begin(CProtocolClientRFB::m_sVERSION.size());
      this->execVersion();
    }
}

void		CProtocolClientRFB::parseSecuList(boost::circular_buffer<char> & rBufferToParse)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::parseSecuList] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (rBufferToParse.size() >= sizeof(unsigned char))
    {
      void* l_pData = rBufferToParse.linearize();
      unsigned char* l_pNbOfSecuTypes = static_cast<unsigned char*>(l_pData);

      if (*l_pNbOfSecuTypes > 0)
	{
	  this->m_cSecuType = 1;
	  this->execSecuList();
	}
      else
	{
	  this->m_oRfbStep = RFB_SECUREASON;
	}
      rBufferToParse.erase_begin(*l_pNbOfSecuTypes + sizeof(unsigned char));
    }
}

void		CProtocolClientRFB::parseSecuResult(boost::circular_buffer<char> & rBufferToParse)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::parseSecuResult] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << rBufferToParse.size() << std::endl;

  if (rBufferToParse.size() >= sizeof(OpenViBE::uint32))
    {
      void* l_pData = rBufferToParse.linearize();

      OpenViBE::uint32* l_pResponse = static_cast<OpenViBE::uint32*>(l_pData);

      if (*l_pResponse == 1)
	{
	  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::zzzzzzz] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	  this->m_oRfbStep = RFB_SECUREASON;
	}
      else
	{
	  if (this->m_ucFirstSecuResult == 0)
	    {
	      std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::ffffffffffffff] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	      this->m_ucFirstSecuResult = 1;
	    }
	  else
	    {
	      std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::zzziiiiiniii] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	      this->m_oRfbStep = RFB_INITMESSAGE;
	      this->execInitMessage();
	    }
	}
      rBufferToParse.erase_begin(sizeof(OpenViBE::uint32));
    }
}

void		CProtocolClientRFB::parseSecuReason(boost::circular_buffer<char> & rBufferToParse)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::parseSecuReason] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (rBufferToParse.size() >= sizeof(OpenViBE::uint32))
    {
      void* l_pData = rBufferToParse.linearize();
      OpenViBE::uint32* l_pReasonLength = static_cast<OpenViBE::uint32*>(l_pData);
      if (*l_pReasonLength > 0)
	{
	  if (rBufferToParse.size() == (*l_pReasonLength + sizeof(OpenViBE::uint32)))
	    {
	      OpenViBE::uint32* l_pTmp = l_pReasonLength;
	      unsigned char* l_pReason = static_cast<unsigned char*>((void *)(++l_pTmp));
	      std::string l_sCloseReason;
	      this->convertUint8ToString(l_pReason, *l_pReasonLength, l_sCloseReason);
	      std::cerr << "[ERROR] - Le serveur a ferme la connection car : " << l_sCloseReason << std::endl;
	      this->m_oRfbStep = RFB_DISCONNECT;
	      rBufferToParse.erase_begin(*l_pReasonLength + sizeof(OpenViBE::uint32));
	    }
	}
      else
	{
	  this->m_oRfbStep = RFB_DISCONNECT;
	  rBufferToParse.erase_begin(sizeof(OpenViBE::uint32));
	}
    }
}

void		CProtocolClientRFB::parseServerInit(boost::circular_buffer<char> & rBufferToParse)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::parseServerInit] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (rBufferToParse.size() >= sizeof(this->m_oDesktopInfo))
    {
      void* l_pData = rBufferToParse.linearize();
      SRFBDesktopInfo* l_opTmpDesktopInfo = static_cast<SRFBDesktopInfo*>(l_pData);
      this->m_oDesktopInfo = *l_opTmpDesktopInfo;
      this->m_oRfbStep = RFB_MESSAGING;
      rBufferToParse.erase_begin(sizeof(this->m_oDesktopInfo));
    }
}

boost::circular_buffer<char> const &	CProtocolClientRFB::parse(boost::circular_buffer<char> & rBufferToParse)
{
  this->m_oMessageToSend.clear();
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CProtocolClientRFB::parse] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (this->m_oParsePtrMap.find(this->m_oRfbStep) != this->m_oParsePtrMap.end())
    {
      funcParsePtr l_tf = this->m_oParsePtrMap[this->m_oRfbStep];
      (this->*l_tf)(rBufferToParse);
    }
  return (this->m_oMessageToSend);
}
