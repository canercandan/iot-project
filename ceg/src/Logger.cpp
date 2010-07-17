#include <Logger.h>
#include <QTime>


Logger::Logger()
{
    this->_currentLogLevel = INFO;
    this->_filename = "Ceg.log";
}

Logger::~Logger()
{

}

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

void    Logger::Log(loglevel msgLogLevel, QString& msg )
{
 QTextStream out(stdout);
 out << "[" << QTime::currentTime().toString().toAscii().data() << "] " << logLevelMsg[msgLogLevel]<< msg;
  //out << "[" << QTime::currentTime().toString().toAscii().data() << "] " << logLevelMsg[msgLogLevel];
}
