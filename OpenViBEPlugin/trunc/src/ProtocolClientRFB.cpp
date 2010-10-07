#include "ProtocolClientRFB.h"

char * const ProtocolClientRFB::_VERSION = "RFB 003.008\n";

ProtocolClientRFB::ProtocolClientRFB():
        _execPtrMap(), _parsePtrMap(), _rfbStep(RFB_VERSION), _secuReason(),
        _secuType(0), _sharedFlag(0), _desktopInfo(0), _messageToSend(0),
        _mouseXPosition(0), _mouseYPosition(0)
{
    _execPtrMap[RFB_VERSION] = &ProtocolClientRFB::execVersion;
    _execPtrMap[RFB_SECULIST] = &ProtocolClientRFB::execSecuList;
    _execPtrMap[RFB_INITMESSAGE] = &ProtocolClientRFB::execInitMessage;
    _execPtrMap[RFB_MESSAGING] = &ProtocolClientRFB::execMessage;

    _parsePtrMap[RFB_VERSION] = &ProtocolClientRFB::parseVersion;
    _parsePtrMap[RFB_SECULIST] = &ProtocolClientRFB::parseSecuList;
    _parsePtrMap[RFB_SECURESULT] = &ProtocolClientRFB::parseSecuResult;
    _parsePtrMap[RFB_SECUREASON] = &ProtocolClientRFB::parseSecuReason;
    _parsePtrMap[RFB_INITMESSAGE] = &ProtocolClientRFB::parseServerInit;
    this->init();
}

void          ProtocolClientRFB::convertUint8ToString(unsigned char * data, int size, std::string & src)
{
    for (int i = 0; i < size; ++i)
    {
        src += data[i];
    }
}

void            ProtocolClientRFB::init()
{
    std::cout << "init" << std::endl;
    this->_rfbStep = RFB_VERSION;
}

void		ProtocolClientRFB::execVersion()
{
    std::cout << "execVersion" << std::endl;
    this->_messageToSend = this->_VERSION;
    this->_rfbStep = RFB_SECULIST;
}

void		ProtocolClientRFB::execSecuList()
{
    std::cout << "execSecuList" << std::endl;
    this->_messageToSend = &this->_secuType;
    this->_rfbStep = RFB_SECURESULT;
}

void		ProtocolClientRFB::execInitMessage()
{
    std::cout << "execInitMessage" << std::endl;
    this->_messageToSend = &this->_sharedFlag;
    this->_rfbStep = RFB_MESSAGING;
}

void		ProtocolClientRFB::execMessage()
{
    std::cout << "execMessage" << std::endl;

}

void	ProtocolClientRFB::exec()
{
    std::cout << "exec" << std::endl;
    funcExecPtr f = 0;
    if (this->_execPtrMap.find(this->_rfbStep) != this->_execPtrMap.end())
    {
        f = this->_execPtrMap[this->_rfbStep];
            (this->*f)();
    }
}

void		ProtocolClientRFB::parseVersion(void * data)
{
    this->execVersion();
}

void		ProtocolClientRFB::parseSecuList(void * data)
{
    unsigned char* nbOfSecuTypes = static_cast<unsigned char*>(data);

    if (nbOfSecuTypes > 0)
    {
        this->_secuType = 1;
        this->execSecuList();
    }
    else
    {
        this->_rfbStep = RFB_SECUREASON;
    }
}

void		ProtocolClientRFB::parseSecuResult(void * data)
{
    std::cout << "parseSecuResult" << std::endl;
    unsigned int* response = static_cast<unsigned int*>(data);

    if (*response == 1)
    {
        this->_rfbStep = RFB_SECUREASON;
    }
    else
    {
        this->execInitMessage();
        this->_rfbStep = RFB_INITMESSAGE;
    }
}

void		ProtocolClientRFB::parseSecuReason(void * data)
{
    unsigned int* reasonLength = static_cast<unsigned int*>(data);
    data += sizeof(unsigned int);
    unsigned char* reason = static_cast<unsigned char*>(data);

    this->convertUint8ToString(reason, *reasonLength, this->_secuReason);
    this->_rfbStep = RFB_DISCONNECT;
}

void		ProtocolClientRFB::parseServerInit(void * data)
{
    std::cout << "parseServerInit" << std::endl;
    this->_desktopInfo = static_cast<RFBDesktopInfo*>(data);


    this->_rfbStep = RFB_MESSAGING;
}

void	ProtocolClientRFB::parse(void * data)
{
    std::cout << "parse" << std::endl;
    funcParsePtr f = 0;
    if (this->_parsePtrMap.find(this->_rfbStep) != this->_parsePtrMap.end())
    {
        f = this->_parsePtrMap[this->_rfbStep];
            (this->*f)(data);
    }
}


RFBServerStep ProtocolClientRFB::getStep() const
{
    std::cout << "getStep" << std::endl;
    return (this->_rfbStep);
}

int ProtocolClientRFB::getWaitedSize() const
{
    std::cout << "getWaitedSize" << std::endl;
    if (this->_rfbStep == RFB_VERSION)
    {
        return (12);
    }
    else if (this->_rfbStep == RFB_KEYMSG)
    {
        return (8);
    }
    else if (this->_rfbStep == RFB_PTRMSG)
    {
        return (6);
    }
    else if (this->_rfbStep == RFB_PASSCHECK)
    {
        return (0);
    }
    return (1);
}
