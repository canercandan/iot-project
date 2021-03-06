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

class QFile;
class QString;
class QTextStream;
class QMutex;

/**
* \enum loglevel
*/
enum loglevel
{
    DEBUG_LOG = 0,
    INFO_LOG = 1,
    WARNING_LOG = 2,
    ERROR_LOG = 3,
};

/**
 * \brief Classe de Log
 * Permet d'enregistrer des informations dans un fichier de log
 */
class Logger
{
public:
    static   Logger* getInstance();
    static   void destroy();

    loglevel getLogLevel() const;
    void    setLogLevel(loglevel newLogLevel);
    QString getLogFile() const;
    void    setLogFile(QString const & filename);

    void    log(loglevel msgLogLevel, QString const & msg);

private:
    Logger();
    ~Logger();

private:
    loglevel _currentLogLevel;
    QFile* _logFile;
    static Logger*  _instance;
    static QMutex   _instanceMutex;
};

#endif // LOGGER_H
