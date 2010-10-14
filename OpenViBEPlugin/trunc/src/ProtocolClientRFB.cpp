#include <iostream> // Remove une fois le debug termine

#include "ProtocolClientRFB.h"

using namespace OpenViBEPlugins::VNC;

char const * ProtocolClientRFB::_VERSION = "RFB 003.008\n";

ProtocolClientRFB::ProtocolClientRFB():
  _parsePtrMap(), _rfbStep(RFB_VERSION), _secuReason(),
  _secuType(0), _sharedFlag(0), _firstSecuResult(0),
  _mouseXPosition(0), _mouseYPosition(0), _mouseMoveDistance(5)
{
  this->_parsePtrMap[RFB_VERSION] = &ProtocolClientRFB::parseVersion;
  this->_parsePtrMap[RFB_SECULIST] = &ProtocolClientRFB::parseSecuList;
  this->_parsePtrMap[RFB_SECURESULT] = &ProtocolClientRFB::parseSecuResult;
  this->_parsePtrMap[RFB_SECUREASON] = &ProtocolClientRFB::parseSecuReason;
  this->_parsePtrMap[RFB_INITMESSAGE] = &ProtocolClientRFB::parseServerInit;
  this->_rfbStep = RFB_VERSION;
}

void		ProtocolClientRFB::initialize(int mouseMoveDistance)
{
  this->_mouseMoveDistance = mouseMoveDistance;
}

bool		ProtocolClientRFB::isInitProcessFinish() const
{
  return (RFB_MESSAGING == this->_rfbStep);
}

void	ProtocolClientRFB::bufcpy(const unsigned char* source, unsigned int length)
{
  std::copy(source, source + length, this->_messageToSend);
}

void	ProtocolClientRFB::convertUint8ToString(unsigned char const * data, unsigned int size, std::string & src)
{
  std::copy(data, data + size, src.begin());
}

VncResult	ProtocolClientRFB::execVersion()
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::execVersion] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  this->bufcpy((const unsigned char*)this->_VERSION, 12);
  this->_rfbStep = RFB_SECULIST;
  return (std::make_pair(this->_messageToSend, 12));
}

VncResult		ProtocolClientRFB::execSecuList()
{
std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::execSecuList] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  this->bufcpy(&this->_secuType, 1);
  this->_rfbStep = RFB_SECURESULT;
  return (std::make_pair(this->_messageToSend, 1));
}

VncResult		ProtocolClientRFB::execInitMessage()
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::execInitMessage] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  this->bufcpy(&this->_sharedFlag, 1);
  this->_rfbStep = RFB_MESSAGING;
  return (std::make_pair(this->_messageToSend, 1));
}

VncResult		ProtocolClientRFB::execKeyMsg(Action action)
{
  RFBKeyEvent	keyEvent;
  keyEvent.messageType = 4;
  keyEvent.downFlag = 1;
  keyEvent.key = (action == ACTION_KEY1 ? 0xff54 : 0xff53);
  
  this->bufcpy((unsigned char*)&keyEvent, sizeof(RFBKeyEvent));
  keyEvent.downFlag = 0;
  this->bufcpy((unsigned char*)&keyEvent, sizeof(RFBKeyEvent));
  return (std::make_pair(this->_messageToSend, sizeof(RFBKeyEvent) * 2));
}

VncResult		ProtocolClientRFB::execMouseMsg(Action action)
{
  RFBPointerEvent	pointerEvent;
  pointerEvent.messageType = 5;
  pointerEvent.buttonMask = 0;
  switch (action)
    {
    case ACTION_MOUSEL:
      if ((this->_mouseXPosition - this->_mouseMoveDistance) <= 0)
	{
	  this->_mouseXPosition = this->_desktopInfo.framebufferWidth;
	}
      else
	this->_mouseXPosition -= this->_mouseMoveDistance;
      break;

    case ACTION_MOUSER:
      if ((this->_mouseXPosition + this->_mouseMoveDistance) > this->_desktopInfo.framebufferWidth)
	{
	  this->_mouseXPosition = 0;
	}
      else
	this->_mouseXPosition += this->_mouseMoveDistance;
      break;

    case ACTION_MOUSEU:
      if ((this->_mouseYPosition - this->_mouseMoveDistance) <= 0)
	{
	  this->_mouseYPosition = this->_desktopInfo.framebufferHeight;
	}
      else
	this->_mouseYPosition -= this->_mouseMoveDistance;
      break;

    case ACTION_MOUSED:
      if ((this->_mouseYPosition + this->_mouseMoveDistance) > this->_desktopInfo.framebufferHeight)
	{
	  this->_mouseYPosition = 0;
	}
      else
	this->_mouseYPosition += this->_mouseMoveDistance;
      break;

    case ACTION_MOUSE1:
      pointerEvent.buttonMask = 1;
      break;

    case ACTION_MOUSE2:
      pointerEvent.buttonMask = 1 << 1;
      break;

    case ACTION_MOUSE3:
      pointerEvent.buttonMask = 1 << 2;
      break;
    default:
      break;
    }
  pointerEvent.xPosition = this->_mouseXPosition;
  pointerEvent.yPosition = this->_mouseYPosition;
  this->bufcpy((unsigned char*)&pointerEvent, sizeof(RFBPointerEvent));
  pointerEvent.buttonMask = 0;
  this->bufcpy((unsigned char*)&pointerEvent, sizeof(RFBPointerEvent));
  return (std::make_pair(this->_messageToSend, sizeof(RFBPointerEvent) * 2));
}

VncResult	ProtocolClientRFB::execute(Action action)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::execute] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (action >= ACTION_KEY1)
    {
      return (this->execKeyMsg(action));
    }
  else
    {
      return (this->execMouseMsg(action));
    }
}

VncResult		ProtocolClientRFB::parseVersion(boost::circular_buffer<char> & bufferToParse)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::parseVersion] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cerr << "TTTTTTTTTTTTTTTaille du buffer pour la version : " << bufferToParse.size() << std::endl;

  std::string rfbVersion(ProtocolClientRFB::_VERSION);
  if (bufferToParse.size() >= rfbVersion.size())
    {
      bufferToParse.erase_begin(rfbVersion.size());
      return (this->execVersion());
    }
  return (std::make_pair(static_cast<char*>(0), 0));
}

VncResult		ProtocolClientRFB::parseSecuList(boost::circular_buffer<char> & bufferToParse)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::parseSecuList] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (bufferToParse.size() >= 2)
    {
      void* data = bufferToParse.linearize();
      unsigned char* nbOfSecuTypes = static_cast<unsigned char*>(data);

      if (*nbOfSecuTypes > 0)
	{
	  this->_secuType = 1;
	  return (this->execSecuList());
	}
      else
	{
	  this->_rfbStep = RFB_SECUREASON;
	}
      bufferToParse.erase_begin(*nbOfSecuTypes + 1);
    }
  return (std::make_pair(static_cast<char*>(0), 0));
}

VncResult		ProtocolClientRFB::parseSecuResult(boost::circular_buffer<char> & bufferToParse)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::parseSecuResult] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (bufferToParse.size() >= 4) // Ne pas mettre des chiffres, utilises de sizeof ou des defines
    {
      void* data = bufferToParse.linearize();

      unsigned int* response = static_cast<unsigned int*>(data);

      if (*response == 1)
	{
	  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::zzzzzzz] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	  this->_rfbStep = RFB_SECUREASON;
	}
      else
	{
	  if (this->_firstSecuResult == 0)
	    {
	      this->_firstSecuResult = 1;
	    }
	  else
	    {
	      std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::zzziiiiiniii] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	      this->_rfbStep = RFB_INITMESSAGE;
	      return (this->execInitMessage());
	    }
	}
      bufferToParse.erase_begin(4);
    }
  return (std::make_pair(static_cast<char*>(0),0));
}

VncResult		ProtocolClientRFB::parseSecuReason(boost::circular_buffer<char> & bufferToParse)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::parseSecuReason] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (bufferToParse.size() >= 4)
    {
      void* data = bufferToParse.linearize();
      unsigned int* reasonLength = static_cast<unsigned int*>(data);
      data += sizeof(unsigned int);
      unsigned char* reason = static_cast<unsigned char*>(data);
	
      this->convertUint8ToString(reason, *reasonLength, this->_secuReason);
      this->_rfbStep = RFB_DISCONNECT;
      bufferToParse.erase_begin(*reasonLength + 4);
    }
  return (std::make_pair(static_cast<char*>(0), 0));
}

VncResult		ProtocolClientRFB::parseServerInit(boost::circular_buffer<char> & bufferToParse)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::parseServerInit] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (bufferToParse.size() >= sizeof(this->_desktopInfo))
    {
      void* data = bufferToParse.linearize();
      RFBDesktopInfo* tmpDesktopInfo = static_cast<RFBDesktopInfo*>(data);
      this->_desktopInfo = *tmpDesktopInfo;
      this->_rfbStep = RFB_MESSAGING;
      bufferToParse.erase_begin(sizeof(this->_desktopInfo));
    }
  return (std::make_pair(static_cast<char*>(0), 0));
}

VncResult	ProtocolClientRFB::parse(boost::circular_buffer<char> & bufferToParse)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [ProtocolClientRFB::parse] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (this->_parsePtrMap.find(this->_rfbStep) != this->_parsePtrMap.end())
    {
      funcParsePtr f = this->_parsePtrMap[this->_rfbStep];
      return ((this->*f)(bufferToParse));
    }
  return (std::make_pair(static_cast<char*>(0), 0));
}
