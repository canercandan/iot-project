// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyright (C) 2010 CEG development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Authors: CEG <ceg@ionlythink.com>, http://www.ionlythink.com
 */

#include "ProtocolServerVNC.h"

#include <QApplication>
#include <QDesktopWidget>

QString const ProtocolServerVNC::_VERSION = "RFB 003.008\n";

ProtocolServerVNC::ProtocolServerVNC():
        _execPtrMap(), _parsePtrMap(), _vncStep(VNC_VERSION), _passOk(TB_UNKNOWN), _validSecurity(true), _secuReason(), _validVersion(false)
{
    _execPtrMap[VNC_VERSION] = &ProtocolServerVNC::execVersion;
    _execPtrMap[VNC_SECULIST] = &ProtocolServerVNC::execSecuList;
    _execPtrMap[VNC_SECURESULT] = &ProtocolServerVNC::execSecuResult;
    _execPtrMap[VNC_SECUREASON] = &ProtocolServerVNC::execSecuReason;
    _execPtrMap[VNC_PASSCHECK] = &ProtocolServerVNC::execSand;
    _execPtrMap[VNC_INITMESSAGE] = &ProtocolServerVNC::execServerInit;

    _parsePtrMap[VNC_VERSION] = &ProtocolServerVNC::parseVersion;
    _parsePtrMap[VNC_SECULIST] = &ProtocolServerVNC::parseSecuList;
    _parsePtrMap[VNC_PASSCHECK] = &ProtocolServerVNC::parsePassword;
    _parsePtrMap[VNC_INITMESSAGE] = &ProtocolServerVNC::parseInitMessage;
    _parsePtrMap[VNC_MESSAGING] = &ProtocolServerVNC::parseMessage;
    this->init();
}

ProtocolServerVNC::~ProtocolServerVNC()
{
}

void          ProtocolServerVNC::convertStringToUint8(QDataStream & src, QString const & data)
{
    for (int i = 0; i < data.size(); ++i)
    {
        src << static_cast<quint8>(data[i].toAscii());
    }
}

void            ProtocolServerVNC::init()
{
    std::cout << "init" << std::endl;
    this->_vncStep = VNC_VERSION;
}

void		ProtocolServerVNC::execVersion(QDataStream & stream)
{
    std::cout << "execVersion" << std::endl;
    this->convertStringToUint8(stream, ProtocolServerVNC::_VERSION);
}

void		ProtocolServerVNC::execSecuList(QDataStream & stream)
{
    std::cout << "execSecuList" << std::endl;
    if (this->_validVersion)
    {
        quint8 nbSecuType = 1;
        quint8 secuTypes = 1;
        stream << nbSecuType << secuTypes;
    }
    else
    {
        quint8 nbSecuType = 0;
        stream << nbSecuType;
        this->_secuReason = "The server cannot support the desired protocol version";
        this->_vncStep = VNC_SECUREASON;
    }
}

void		ProtocolServerVNC::execSecuResult(QDataStream & stream)
{
    std::cout << "execSecuResult" << std::endl;
    quint32 response = (this->_validSecurity ? 0 : 1);
    stream << response;

    if (response == 1)
    {
        if (this->_passOk == TB_FALSE)
        {
            this->_secuReason = "Password is not valid !";
        }
        else
        {
            this->_secuReason = "Desired security type does not exist !";
        }
        this->_vncStep = VNC_SECUREASON;
    }
    else if (this->_passOk == TB_UNKNOWN)
    {
        this->_vncStep = VNC_INITMESSAGE;
	//        this->_vncStep = VNC_PASSCHECK;
    }
    else
    {
        this->_vncStep = VNC_INITMESSAGE;
    }
}

void		ProtocolServerVNC::execSecuReason(QDataStream & stream)
{
    std::cout << "execSecuReason" << std::endl;
    stream << static_cast<quint8>(this->_secuReason.size());
    this->convertStringToUint8(stream, this->_secuReason);
}

void		ProtocolServerVNC::execSand(QDataStream & stream)
{
    std::cout << "execSand" << std::endl;
    // if the secuType is none, then we pass to the result step
    if (this->_secuType == 1)
    {
        this->_passOk = TB_TRUE;
        this->_vncStep = VNC_SECURESULT;
        this->execSecuResult(stream);
    }
}

void		ProtocolServerVNC::execServerInit(QDataStream & stream)
{
    std::cout << "execServerInit" << std::endl;
    QDesktopWidget *desktop = QApplication::desktop();
    VNCDesktopInfo desktopInfo;

    desktopInfo.framebufferHeight = static_cast<qint16>(desktop->height());
    desktopInfo.framebufferWidth = static_cast<qint16>(desktop->width());
    desktopInfo.nameLength = static_cast<qint32>(4);
    desktopInfo.nameString[0] = static_cast<qint8>('I');
    desktopInfo.nameString[1] = static_cast<qint8>('O');
    desktopInfo.nameString[2] = static_cast<qint8>('T');
    desktopInfo.nameString[2] = static_cast<qint8>('.');
    desktopInfo.serverPixelFormat.bitsPerPixel = static_cast<qint8>(32);
    desktopInfo.serverPixelFormat.depth = static_cast<qint8>(32);
    desktopInfo.serverPixelFormat.bigEndianFlag = static_cast<qint8>(1);
    desktopInfo.serverPixelFormat.trueColourFlag = static_cast<qint8>(0);
    desktopInfo.serverPixelFormat.redMax = static_cast<qint16>(0);
    desktopInfo.serverPixelFormat.greenMax = static_cast<qint16>(0);
    desktopInfo.serverPixelFormat.blueMax = static_cast<qint16>(0);
    desktopInfo.serverPixelFormat.redShift = static_cast<qint8>(0);
    desktopInfo.serverPixelFormat.greenShift = static_cast<qint8>(0);
    desktopInfo.serverPixelFormat.blueShift = static_cast<qint8>(0);

    std::cout << "DesktopInfo size : " << sizeof(desktopInfo) << std::endl;
    std::cout << "serverPixelFormat size : " << sizeof(desktopInfo.serverPixelFormat) << std::endl;

    std::cout << "Name size : " << sizeof(desktopInfo.nameString) << std::endl;

    //    stream.writeBytes((char *)&desktopInfo, sizeof(desktopInfo));
    stream << desktopInfo.framebufferWidth << desktopInfo.framebufferHeight << desktopInfo.serverPixelFormat.bitsPerPixel;
    stream << desktopInfo.serverPixelFormat.depth << desktopInfo.serverPixelFormat.bigEndianFlag;
    stream << desktopInfo.serverPixelFormat.trueColourFlag << desktopInfo.serverPixelFormat.redMax;
    stream << desktopInfo.serverPixelFormat.greenMax << desktopInfo.serverPixelFormat.blueMax;
    stream << desktopInfo.serverPixelFormat.redShift << desktopInfo.serverPixelFormat.greenShift;
    stream << desktopInfo.serverPixelFormat.blueShift << desktopInfo.serverPixelFormat.padding;
    stream << desktopInfo.nameLength << desktopInfo.nameString;

    this->_vncStep = VNC_MESSAGING;
}


void	ProtocolServerVNC::exec(QDataStream & stream)
{
    std::cout << "exec" << std::endl;
    funcExecPtr f = 0;
    if (this->_execPtrMap.contains(this->_vncStep))
    {
        f = this->_execPtrMap.value(this->_vncStep);
        (this->*f)(stream);
    }
}


void		ProtocolServerVNC::parseVersion(QDataStream & data)
{
    QString version;
    std::cout << "parseVersion" << std::endl;
    for (int i = 0; i < 12; ++i)
    {
        quint8 tmp;
        data >> tmp;
        std::cout << (int)tmp << std::endl;
        version +=  tmp;
    }

    if (this->_VERSION.compare(version) == 0)
    {
        std::cout << "ValidVersion" << std::endl;
        this->_validVersion = true;
    }
    else
        std::cout << "NotValidVersion" << std::endl;
    this->_validVersion = true;
    std::cout << version.toStdString() << " " << version.size() << std::endl;
    std::cout << this->_VERSION.toStdString() << " " << this->_VERSION.size() << std::endl;
    this->_vncStep = VNC_SECULIST;
}

void		ProtocolServerVNC::parseSecuList(QDataStream & data)
{
    std::cout << "parseSecuList" << std::endl;
    this->_validSecurity = true;
    data >> this->_secuType;
    std::cout << "SecurityType: " << (int)this->_secuType << std::endl;
    this->_validSecurity = (this->_secuType == 1 ? true : false);
    this->_vncStep = VNC_SECURESULT;
}

void		ProtocolServerVNC::parsePassword(QDataStream & data)
{
    std::cout << "parsePassword" << std::endl;
    // there is no password, then we pass to the next step
    if (1)
    {
        this->_validSecurity = true;
        this->_passOk = TB_TRUE;
    }
    else //password not valid message
    {
        this->_validSecurity = false;
        this->_passOk = TB_FALSE;
    }
    this->_vncStep = VNC_SECURESULT;
}

void		ProtocolServerVNC::parseInitMessage(QDataStream & data)
{
    std::cout << "parseInitMessage" << std::endl;
    quint8 sharedFlag;
    data >> sharedFlag;
}

void		ProtocolServerVNC::parseMessage(QDataStream & data)
{
    std::cout << "parseMessage" << std::endl;
    quint8  messageType;
    data >> messageType;
    if (messageType == 4)
    {
        this->_vncStep = VNC_KEYMSG;
    }
    else if (messageType == 5)
    {
        this->_vncStep = VNC_PTRMSG;
    }
    else
    {
        // CLOSE CONNECTION
        this->_validSecurity = false;
        this->_secuReason = "Server cannot identify the message type !";
        this->_vncStep = VNC_SECUREASON;
    }
}

void	ProtocolServerVNC::parse(QDataStream & data)
{
    std::cout << "parse" << std::endl;
    funcParsePtr f = 0;
    if (this->_parsePtrMap.contains(this->_vncStep))
    {
        f = this->_parsePtrMap.value(this->_vncStep);
        (this->*f)(data);
    }
}


VNCServerStep ProtocolServerVNC::getStep() const
{
    std::cout << "getStep" << std::endl;
    return (this->_vncStep);
}

int ProtocolServerVNC::getWaitedSize() const
{
    std::cout << "getWaitedSize" << std::endl;
    if (this->_vncStep == VNC_VERSION)
    {
        return (12);
    }
    else if (this->_vncStep == VNC_KEYMSG)
    {
        return (8);
    }
    else if (this->_vncStep == VNC_PTRMSG)
    {
        return (6);
    }
    else if (this->_vncStep == VNC_PASSCHECK)
    {
        return (0);
    }
    return (1);
}
