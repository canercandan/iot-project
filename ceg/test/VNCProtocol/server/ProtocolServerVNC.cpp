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


QString const ProtocolServerVNC::_VERSION = "RFB 003.008\n";

ProtocolServerVNC::ProtocolServerVNC():
        _execPtrMap(), _parsePtrMap(), _vncStep(VNCServerStep::VNC_VERSION), _passOk(triBool::TB_UNKNOWN), _validSecurity(true), _secuReason()
{
    _execPtrMap[VNCServerStep::VNC_VERSION] = &ProtocolServerVNC::execVersion;
    _execPtrMap[VNCServerStep::VNC_SECULIST] = &ProtocolServerVNC::execVSecuList;
    _execPtrMap[VNCServerStep::VNC_SECURESULT] = &ProtocolServerVNC::execSecuResult;
    _execPtrMap[VNCServerStep::VNC_SECUREASON] = &ProtocolServerVNC::execSecuReason;
    _execPtrMap[VNCServerStep::VNC_PASSCHECK] = &ProtocolServerVNC::execSand;
    _execPtrMap[VNCServerStep::VNC_INITMESSAGE] = &ProtocolServerVNC::execServerInit;

    _parsePtrMap[VNCServerStep::VNC_VERSION] = &ProtocolServerVNC::parseVersion;
    _parsePtrMap[VNCServerStep::VNC_SECULIST] = &ProtocolServerVNC::parseSecuList;
    _parsePtrMap[VNCServerStep::VNC_SECUFAIL] = &ProtocolServerVNC::parseSecuFail;
    _parsePtrMap[VNCServerStep::VNC_PASSCHECK] = &ProtocolServerVNC::parsePassword;
    _parsePtrMap[VNCServerStep::VNC_INITMESSAGE] = &ProtocolServerVNC::parseInitMessage;
    _parsePtrMap[VNCServerStep::VNC_MESSAGING] = &ProtocolServerVNC::parseMessage;
    this->init();
}

ProtocolServerVNC::~ProtocolServerVNC()
{
}

void          ProtocolServerVNC::convertStringToUint8(QDataStream & src, QString const & data)
{
    for (int i = 0; i < data.size(); ++i)
    {
        src << static_cast<quint8>(data[i]);
    }
}

void            ProtocolServerVNC::init()
{
    this->_vncStep = VNCServerStep::VNC_VERSION;
}

void		ProtocolServerVNC::execVersion(QDataStream & stream)
{
    this->convertStringToUint8(stream, ProtocolServerVNC::_VERSION);
}

void		ProtocolServerVNC::execSecuList(QDataStream & stream)
{
    quint8 nbSecuType = 1;
    quint8 secuTypes[0] = 1;
    stream << nbSecuType << secuTypes;
}

void		ProtocolServerVNC::execSecuResult(QDataStream & stream)
{
    quint32 response = (this->_validSecurity ? 0 : 1);
    stream << response;

    if (response == 1)
    {
        if (this->_passOk == triBool::TB_FALSE)
        {
            this->_secuReason = "Password is not valid !";
        }
        else
        {
            this->_secuReason = "Desired security type does not exist !";
        }
        this->_vncStep = VNCServerStep::VNC_SECUREASON;
    }
    else if (this->_passOk == triBool::TB_UNKNOWN)
    {
        this->_vncStep = VNCServerStep::VNC_PASSCHECK;
    }
    else
    {
        this->_vncStep = VNCServerStep::VNC_INITMESSAGE;
    }
}

void		ProtocolServerVNC::execSecuReason(QDataStream & stream)
{
    stream << static_cast<quint8>(this->_secuReason.size());
    this->convertStringToUint8(stream, this->_secuReason);
}

void		ProtocolServerVNC::execSand(QDataStream & stream)
{
    // if the secuType is none, then we pass to the result step
    if (this->_secuType == 1)
    {
        this->_vncStep = VNCServerStep::VNC_SECURESULT;
        this->execSecuResult(stream);
    }
}

void		ProtocolServerVNC::execServerInit(QDataStream & stream)
{

    this->_vncStep = VNCServerStep::VNC_MESSAGING;
}


QString	ProtocolServerVNC::exec()
{
}


void		ProtocolServerVNC::parseVersion(QDataStream & data, QString &)
{

    if (1)
    {
        this->_vncStep = VNCServerStep::VNC_SECULIST;
    }
}

void		ProtocolServerVNC::parseSecuList(QDataStream & data, QString &)
{
    this->_validSecurity = true;
    this->_secuType = 1;
    if (this->_secuType != 1)
    {
        this->_vncStep = VNCServerStep::VNC_SECUFAIL;
    }
    else
    {
        this->_vncStep = VNCServerStep::VNC_SECURESULT;
    }
}

void		ProtocolServerVNC::parseSecuFail(QDataStream & data, QString &)
{

}

void		ProtocolServerVNC::parsePassword(QDataStream & data, QString &)
{

    //password not valid message
    if (0)
    {
        this->_passOk = triBool::TB_FALSE;
        this->_validSecurity = false;
    }
    else
    {
        this->_passOk = triBool::TB_TRUE;
    }

    // there is no password, then we pass to the next step
    if (1)
    {
        this->_vncStep = VNCServerStep::VNC_SECURESULT;
    }
}

void		ProtocolServerVNC::parseInitMessage(QDataStream & data, QString &)
{

}

void		ProtocolServerVNC::parseMessage(QDataStream & data, QString &)
{

}

QString	ProtocolServerVNC::parse(QDataStream & data)
{
}


VNCServerStep ProtocolServerVNC::getStep() const
{
    return (this->_vncStep);
}
