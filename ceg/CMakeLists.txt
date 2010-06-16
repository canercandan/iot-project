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
### 6) Include packaging features
######################################################################################

#cpack package information
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(CPACK_PACKAGE_DESCRIPTION "CEG has been developped as part of IOT project and allows to users to control machine by thinking.")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Graphical Environment Control")
SET(CPACK_PACKAGE_VENDOR "IOT")
SET(CPACK_PACKAGE_CONTACT "ceg@ionlythink.com")
SET(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
SET(CPACK_STRIP_FILES ${PROJECT_NAME})
SET(CPACK_SOURCE_STRIP_FILES "bin/${PROJECT_NAME}")
SET(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "${PROJECT_NAME}")
SET(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME} ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

#SET(CPACK_GENERATOR "DEB")

INCLUDE(CPack)

######################################################################################
