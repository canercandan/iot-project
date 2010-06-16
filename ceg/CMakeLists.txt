######################################################################################
### 1) Set the application properties
######################################################################################

# Checks cmake version compatibility
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(ceg)

SET(PROJECT_VERSION_MAJOR 1)
SET(PROJECT_VERSION_MINOR 0)
SET(PROJECT_VERSION_PATCH 0)
SET(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

######################################################################################


######################################################################################
### 2) Include useful features
######################################################################################

INCLUDE(FindDoxygen)

# see http://cmake.org/cmake/help/cmake2.6docs.html#module:FindQt4 for a complete list
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtNetwork QtXml REQUIRED)
INCLUDE(${QT_USE_FILE})

######################################################################################


######################################################################################
### 3) Include header files path
######################################################################################

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/includes
  ${CMAKE_SOURCE_DIR}/includes/Action
  )

######################################################################################


######################################################################################
### 4) Set compiler definitions
######################################################################################

IF(UNIX)
  # enable warnings
  ADD_DEFINITIONS( -Wall -W -Wextra )
  # ADD_DEFINITIONS( -Weffc++)
#   ADD_DEFINITIONS( -g3 )
ENDIF()

######################################################################################


######################################################################################
### 5) Now where we go ?
######################################################################################

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(config)
#ADD_SUBDIRECTORY(resources)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(doc)

######################################################################################


######################################################################################
### 6) Include packaging
######################################################################################

INCLUDE(Packaging.cmake)

######################################################################################
