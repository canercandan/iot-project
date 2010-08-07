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
#include <iostream>
/*********************************/
#include <QFile>
#include <QTime>
#include <QTextStream>
#include <QMutex>
/*********************************/
#include "Logger.h"
/*********************************/

static const char* logLevelMsg[4] = {"DEBUG: ", "INFO: ", "WARNING: ", "ERROR: "};

/************************************************* [ CTOR/DTOR ] *************************************************/

Logger* Logger::_instance;
QMutex Logger::_instanceMutex;

Logger::Logger()
{
    this->_currentLogLevel = DEBUG_LOG;
    this->_logFile = new QFile("Ceg.log");
    if(!this->_logFile->open(QIODevice::WriteOnly | QIODevice::Append))
    {
	this->log(WARNING_LOG, "Failed to open Ceg.log");
    }
}

Logger::~Logger()
{
    std::cerr << "Logger::~Logger()" << std::endl;
    if (this->_logFile != 0)
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


//! set a File
void    Logger::setLogFile(QString const & filename)
{
    if (this->_logFile)
    {
	this->_logFile->close();
	delete this->_logFile;
    }
    this->_logFile = new QFile(filename);
    if(!this->_logFile->open(QIODevice::WriteOnly | QIODevice::Append))
    {
	QString msg;
	QTextStream tmp(&msg);
	tmp << "Failed to open log file: " << filename;
	this->log(WARNING_LOG, msg);
    }
}


QString    Logger::getLogFile() const
{
    return (this->_logFile->fileName());
}

void    Logger::log(loglevel msgLogLevel,QString const & msg)
{
    this->log(msgLogLevel, msg.toStdString().c_str());
}

void    Logger::log(loglevel msgLogLevel, const char *msg)
{
    if (this->_currentLogLevel > msgLogLevel)
	return;
    QTextStream out(stdout);
    out << "[" << QTime::currentTime().toString().toAscii().data() << "] " << logLevelMsg[msgLogLevel]<< msg << endl;
    if (this->_logFile && this->_logFile->exists())
    {
	QTextStream filestream(this->_logFile);
	filestream << "[" << QTime::currentTime().toString().toAscii().data() << "] " << logLevelMsg[msgLogLevel]<< msg << endl;
    }
}

void Logger::log(loglevel msgLogLevel, QTextStream const & msg)
{
    QString* tmp = msg.string();
    this->log(msgLogLevel, *tmp);
}


Logger* Logger::getInstance()
{
    QMutexLocker instanceMutexLocker(&Logger::_instanceMutex);
    if (!_instance)
    {
	Logger::_instance = new Logger;
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
