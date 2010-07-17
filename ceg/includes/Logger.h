#ifndef LOGGER_H
#define LOGGER_H

#include <QTextStream>

enum loglevel
{
    INFO = 0,
    DEBUG = 1,
    WARNING = 2,
    ERROR = 3,
};

static const char* logLevelMsg[4] = {"INFO", "DEBUG", "WARNING", "ERROR: "};

class Logger
{
    //friend class Singleton<Logger>;
public:
    loglevel getLogLevel() const;
    void    setLogLevel(loglevel newLogLevel);
    void    setLogFile(QString filename);
    QString& getLogFile();
    void    Log(loglevel msgLogLevel, QString& msg);
private:
    Logger();
    ~Logger();
    loglevel _currentLogLevel;
    QString _filename;
};

#endif // LOGGER_H
