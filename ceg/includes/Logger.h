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
 #ifndef LOGGER_H
#define LOGGER_H

#include <QString>



enum loglevel
{
    INFO_LOG = 0,
    DEBUG_LOG = 1,
    WARNING_LOG = 2,
    ERROR_LOG = 3,
};

/**
 * \brief Classe de Log
 * Permet d'enregistrer du log
 */
class Logger
{
    public:

    //friend class Singleton<Logger>;
   static   Logger* getInstance();
   static   void destroy();
   loglevel getLogLevel() const;
    void    setLogLevel(loglevel newLogLevel);
    void    setLogFile(QString filename);
    QString& getLogFile();
    void    Log(loglevel msgLogLevel, QString& msg);
    void    Log(loglevel msgLogLevel, const char *msg);
private:
    Logger();
    ~Logger();
    loglevel _currentLogLevel;
    QString _filename;
    static Logger*  _instance;
};

#endif // LOGGER_H
