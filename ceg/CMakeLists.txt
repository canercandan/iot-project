CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(ceg)

SET(PACKAGE_NAME "IOT Graphical Environment Control" CACHE STRING "Package name" FORCE)
SET(PACKAGE_VERSION "1.0" CACHE STRING "Package version" FORCE)

INCLUDE(FindDoxygen)

# see http://cmake.org/cmake/help/cmake2.6docs.html#module:FindQt4 for a complete list
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtNetwork QtXml REQUIRED)
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/includes)

IF(UNIX)
  # enable warnings
  ADD_DEFINITIONS( -Wall -W -Wextra )
  # ADD_DEFINITIONS( -Weffc++)
  # ADD_DEFINITIONS( -g3 )
ENDIF()

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(config)
#ADD_SUBDIRECTORY(resources)
ADD_SUBDIRECTORY(test)

ADD_SUBDIRECTORY(doc)
