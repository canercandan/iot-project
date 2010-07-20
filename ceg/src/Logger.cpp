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
/*********************************/
#include <Logger.h>
/*********************************/

static const char* logLevelMsg[4] = {"INFO: ", "DEBUG: ", "WARNING: ", "ERROR: "};

/************************************************* [ CTOR/DTOR ] *************************************************/

Logger* Logger::_instance = 0;

Logger::Logger()
{
    this->_currentLogLevel = INFO_LOG;
    this->_filename = "Ceg.log";
}

Logger::~Logger()
{
    //FIXME close le handle sur fichier
    //delete this->_filename;
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
    this->_filename = filename;
}


QString&    Logger::getLogFile()
{
    return (this->_filename);
}

void    Logger::Log(loglevel msgLogLevel,QString& msg)
{
    QTextStream out(stdout);
    out << "[" << QTime::currentTime().toString().toAscii().data() << "] " << logLevelMsg[msgLogLevel]<< msg;
}

void    Logger::Log(loglevel msgLogLevel,const char *msg)
{

    QTextStream out(stdout);
    out << "[" << QTime::currentTime().toString().toAscii().data() << "] " << logLevelMsg[msgLogLevel]<< msg;
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
