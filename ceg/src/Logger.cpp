#include <QTime>
#include <QTextStream>
#include <Logger.h>

static const char* logLevelMsg[4] = {"INFO: ", "DEBUG: ", "WARNING: ", "ERROR: "};

Logger* Logger::_instance = 0;

Logger::Logger()
{
    this->_currentLogLevel = INFO;
    this->_filename = "Ceg.log";
}

Logger::~Logger()
{
    //FIXME close le handle sur fichier
    //delete this->_filename;
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
