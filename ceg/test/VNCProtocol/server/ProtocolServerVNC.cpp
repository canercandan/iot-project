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

ProtocolServerVNC::ProtocolServerVNC():
        _execPtrMap(), _parsePtrMap(), _vncStep(vncServerStep::VNC_VERSION), _passOk(triBool::TB_UNKNOWN)
{
  _execPtrMap[vncServerStep::VNC_VERSION] = &ProtocolServerVNC::execVersion;
  _execPtrMap[vncServerStep::VNC_SECULIST] = &ProtocolServerVNC::execVSecuList;
  _execPtrMap[vncServerStep::VNC_SECURESULT] = &ProtocolServerVNC::execSecuResult;
  _execPtrMap[vncServerStep::VNC_SECUREASON] = &ProtocolServerVNC::execSecuReason;
  _execPtrMap[vncServerStep::VNC_PASSCHECK] = &ProtocolServerVNC::execSand;
  _execPtrMap[vncServerStep::VNC_INITMESSAGE] = &ProtocolServerVNC::execServerInit;

  _parsePtrMap[vncServerStep::VNC_VERSION] = &ProtocolServerVNC::parseVersion;
  _parsePtrMap[vncServerStep::VNC_SECULIST] = &ProtocolServerVNC::parseSecuList;
  _parsePtrMap[vncServerStep::VNC_SECUFAIL] = &ProtocolServerVNC::parseSecuFail;
  _parsePtrMap[vncServerStep::VNC_PASSCHECK] = &ProtocolServerVNC::parsePassword;
  _parsePtrMap[vncServerStep::VNC_INITMESSAGE] = &ProtocolServerVNC::parseInitMessage;
}

ProtocolServerVNC::~ProtocolServerVNC()
{
}

void            ProtocolServerVNC::init()
{
    this->_vncStep = vncServerStep::VNC_VERSION;
}

void		ProtocolServerVNC::execVersion(QDataStream & stream)
{
    stream << "RFB 003.008\n";
}

void		ProtocolServerVNC::execSecuList(QDataStream & stream)
{
    qint8 nbSecuType = 1;
    qint8 secuTypes[0] = 1;
    stream << nbSecuType << secuTypes;
}

void		ProtocolServerVNC::execSecuResult(QDataStream & stream)
{

    if (this->_passOk == triBool::TB_FALSE)
    {
        this->_vncStep = vncServerStep::VNC_SECUREASON;
    }
    else if (this->_passOk == triBool::TB_UNKNOWN)
    {
        this->_vncStep = vncServerStep::VNC_PASSCHECK;
    }
    else
    {
        this->_vncStep = vncServerStep::VNC_INITMESSAGE;
    }
}

void		ProtocolServerVNC::execSecuReason(QDataStream & stream)
{
    if (this->_passOk == triBool::TB_FALSE)
    {
        ""
    }
}

void		ProtocolServerVNC::execSand(QDataStream & stream)
{

    if (0)
    {
        this->_vncStep = vncServerStep::VNC_INITMESSAGE;
    }
}

void		ProtocolServerVNC::execServerInit(QDataStream & stream)
{

}


QString	ProtocolServerVNC::exec()
{
}


void		ProtocolServerVNC::parseVersion(char *, QString &)
{

    if (1)
    {
        this->_vncStep = vncServerStep::VNC_SECULIST;
    }
}

void		ProtocolServerVNC::parseSecuList(char *, QString &)
{

    if (0)
    {
        this->_vncStep = vncServerStep::VNC_SECUFAIL;
    }
    else
    {
        this->_vncStep = vncServerStep::VNC_SECURESULT;
    }
}

void		ProtocolServerVNC::parseSecuFail(char *, QString &)
{

}

void		ProtocolServerVNC::parsePassword(char *, QString &)
{

    if (1)
    {
        this->_vncStep = vncServerStep::VNC_SECURESULT;
    }
}

void		ProtocolServerVNC::parseInitMessage(char *, QString &)
{

}


QString	ProtocolServerVNC::parse(char *)
{
}
