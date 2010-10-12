#include "ProtocolClientRFB.h"

using namespace OpenViBEPlugins::VNC;

char const * ProtocolClientRFB::_VERSION = "RFB 003.008\n";

ProtocolClientRFB::ProtocolClientRFB():
        _parsePtrMap(), _rfbStep(RFB_VERSION), _secuReason(),
        _secuType(0), _sharedFlag(0), _desktopInfo(0), 
        _mouseXPosition(0), _mouseYPosition(0), _mouseMoveDistance(5)
{
    _parsePtrMap[RFB_VERSION] = &ProtocolClientRFB::parseVersion;
    _parsePtrMap[RFB_SECULIST] = &ProtocolClientRFB::parseSecuList;
    _parsePtrMap[RFB_SECURESULT] = &ProtocolClientRFB::parseSecuResult;
    _parsePtrMap[RFB_SECUREASON] = &ProtocolClientRFB::parseSecuReason;
    _parsePtrMap[RFB_INITMESSAGE] = &ProtocolClientRFB::parseServerInit;
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

void	ProtocolClientRFB::bufcpy(char* source, int length)
{
  for (int i = 0; i < length; ++i)
    {
      this->_messageToSend[i] = source[i];
    }
}

void	ProtocolClientRFB::convertUint8ToString(unsigned char * data, int size, std::string & src)
{
  for (int i = 0; i < size; ++i)
    {
      src += data[i];
    }
}

VncResult	ProtocolClientRFB::execVersion()
{
  std::cout << "execVersion" << std::endl;
  this->bufcpy(this->_VERSION, 12);
  this->_rfbStep = RFB_SECULIST;
  return (std::make_pair(this->_messageToSend, 12));
}

VncResult		ProtocolClientRFB::execSecuList()
{
  std::cout << "execSecuList" << std::endl;
  this->bufcpy(this->_secuType, 1);
  this->_rfbStep = RFB_SECURESULT;
  return (std::make_pair(this->_messageToSend, 1));
}

VncResult		ProtocolClientRFB::execInitMessage()
{
  std::cout << "execInitMessage" << std::endl;
  this->bufcpy(this->_sharedFlag, 1);
  this->_rfbStep = RFB_MESSAGING;
  return (std::make_pair(this->_messageToSend, 1));
}

VncResult		ProtocolClientRFB::execKeyMsg(Action action)
{
  RFBKeyEvent	keyEvent;
  keyEvent.messageType = 4;
  keyEvent.downFlag = 1;
  keyEvent.key = (action == ACTION_KEY1 ? 0xff54 : 0xff53);
  
  this->bufcpy(&keyEvent, 8);
  keyEvent.downFlag = 0;
  this->bufcpy(&keyEvent, 8);
  return (std::make_pair(this->_messageToSend, 16));
}

VncResult		ProtocolClientRFB::execMouseMsg(Action)
{
  return (std::make_pair(0, 0));
}


VncResult	ProtocolClientRFB::execute(Action action)
{
    std::cout << "exec" << std::endl;
    if (action == ACTION_KEY1 && action == ACTION_KEY2)
      {
	return (this->execKeyMsg(action));
      }
    else
      {
	return (this->execMouseMsg(action));
      }
}

VncResult		ProtocolClientRFB::parseVersion(void * data)
{
  return (this->execVersion());
}

VncResult		ProtocolClientRFB::parseSecuList(void * data)
{
    unsigned char* nbOfSecuTypes = static_cast<unsigned char*>(data);

    if (nbOfSecuTypes > 0)
    {
        this->_secuType = 1;
        return (this->execSecuList());
    }
    else
    {
        this->_rfbStep = RFB_SECUREASON;
    }
    return (std::make_pair(0, 0));
}

VncResult		ProtocolClientRFB::parseSecuResult(void * data)
{
    std::cout << "parseSecuResult" << std::endl;
    unsigned int* response = static_cast<unsigned int*>(data);

    if (*response == 1)
    {
      this->_rfbStep = RFB_SECUREASON;
    }
    else
    {
      this->_rfbStep = RFB_INITMESSAGE;
      return (this->execInitMessage());
    }
    return (std::make_pair(0,0));
}

VncResult		ProtocolClientRFB::parseSecuReason(void * data)
{
    unsigned int* reasonLength = static_cast<unsigned int*>(data);
    data += sizeof(unsigned int);
    unsigned char* reason = static_cast<unsigned char*>(data);

    this->convertUint8ToString(reason, *reasonLength, this->_secuReason);
    this->_rfbStep = RFB_DISCONNECT;
    return (std::make_pair(0, 0));
}

VncResult		ProtocolClientRFB::parseServerInit(void * data)
{
    std::cout << "parseServerInit" << std::endl;
    this->_desktopInfo = static_cast<RFBDesktopInfo*>(data);


    this->_rfbStep = RFB_MESSAGING;
    return (std::make_pair(0, 0));
}

VncResult	ProtocolClientRFB::parse(boost::circular_buffer<char> & bufferToParse)
{
  #warning "Voila j ai change la signature de ta fonction, je te donne le buffer directement lis le commentatire dessous"
  /*
    Il y a un acces sequentiel ou par iterateur dans le buffer
    Par contre une fois que tu as lu ce que tu voulais tu dois le consommer en utilisant la methode:
    boost::circular_buffer::erase_begin(Nombre de bytes a consommer);
   */
    std::cout << "parse" << std::endl;
    funcParsePtr f = 0;
    if (this->_parsePtrMap.find(this->_rfbStep) != this->_parsePtrMap.end())
    {
        f = this->_parsePtrMap[this->_rfbStep];
	//return ((this->*f)(data));
    }
    return (std::make_pair(0, 0));
}


RFBServerStep ProtocolClientRFB::getStep() const
{
    std::cout << "getStep" << std::endl;
    return (this->_rfbStep);
}
