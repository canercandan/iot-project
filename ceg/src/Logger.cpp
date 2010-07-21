// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyleft (C) 2010 CEG development team
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

/*********************************/
#include <QTime>
#include <QTextStream>
#include <stdio.h>  //FOR IO MACROS
/*********************************/
#include "Logger.h"
/*********************************/

static const char* logLevelMsg[4] = {"DEBUG: ", "INFO: ", "WARNING: ", "ERROR: "};

/************************************************* [ CTOR/DTOR ] *************************************************/

Logger* Logger::_instance = 0;

Logger::Logger()
{
    this->_currentLogLevel = DEBUG_LOG;
    this->_logFile = new QFile("Ceg.log");
    if (!this->_logFile->exists())
        this->Log(WARNING_LOG, "Ceg.log does not exist");
    else
    {
        if(!this->_logFile->open(QIODevice::WriteOnly | QIODevice::Append))
          {
            this->Log(WARNING_LOG, "Failed to open Ceg.log");
          }
    }
}

Logger::~Logger()
{
    if (this->_logFile)
    {
        this->_logFile->close();
       delete this->_logFile;
    }
}

/************************************************* [ OTHERS ] *************************************************/

loglevel Logger::getLogLevel() const
{
    return (this->_currentLogLevel);
}

void    Logger::setLogLevel(loglevel newLogLevel)
{
    this->_currentLogLevel = newLogLevel;
}



void    Logger::setLogFile(QString filename)
{
    //FIXME close le previous file si exist

    if (this->_logFile)
    {
        this->_logFile->close();
        delete this->_logFile;
    }
    this->_logFile = new QFile(filename);
    if (!this->_logFile->exists())
    {
        this->Log(WARNING_LOG, "This log File doest not exist");
    }
    else
    {
        if(!this->_logFile->open(QIODevice::WriteOnly | QIODevice::Append))
        {
            this->Log(WARNING_LOG, "Failed to open log file");
        }
    }
}


QString const    Logger::getLogFile() const
{
    return (this->_logFile->fileName());
}

void    Logger::Log(loglevel msgLogLevel,QString& msg)
{
    this->Log(msgLogLevel, msg.toStdString().c_str());
}

void    Logger::Log(loglevel msgLogLevel, const char *msg)
{
    if (this->_currentLogLevel > msgLogLevel)
        return;
    QTextStream out(stdout);

    out << "[" << QTime::currentTime().toString().toAscii().data() << "] " << logLevelMsg[msgLogLevel]<< msg << "\r\n";
    if (this->_logFile && this->_logFile->exists())
    {
     QTextStream filestream(this->_logFile);
     filestream << "[" << QTime::currentTime().toString().toAscii().data() << "] " << logLevelMsg[msgLogLevel]<< msg;
    }

}

Logger* Logger::getInstance()
{
    if (!_instance)
    {
	Logger::_instance = new Logger();
    }
    return Logger::_instance;
}

void Logger::destroy()
{
    if (Logger::_instance)
    {
	delete Logger::_instance;
	Logger::_instance = 0;
    }
}
