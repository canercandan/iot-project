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
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtNetwork QtXml QtXmlPatterns REQUIRED)
INCLUDE(${QT_USE_FILE})

IF (UNIX)
  INCLUDE(FindPkgConfig)

  PKG_CHECK_MODULES(XMU xmu REQUIRED)
  PKG_CHECK_MODULES(XTST xtst REQUIRED)

  INCLUDE_DIRECTORIES(${XMU_INCLUDE_DIR} ${XTST_INCLUDE_DIR})
  LINK_DIRECTORIES(${XMU_LIBRARY_DIRS} ${XTST_LIBRARY_DIRS})
ENDIF()

######################################################################################


######################################################################################
### 3) Include header files path
######################################################################################

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/Action
  )

######################################################################################


######################################################################################
### 4) Set compiler definitions
######################################################################################

IF(UNIX)
  # enable warnings
  ADD_DEFINITIONS( -Wall -W -Wextra )
  # ADD_DEFINITIONS( -Weffc++)
  ADD_DEFINITIONS( -g3 )
ENDIF()

######################################################################################


######################################################################################
### 5) Prepare some variables for CMAKE usage
######################################################################################

SET(SAMPLE_SRCS)
SET(SAMPLE_UIS)
SET(SAMPLE_MOC_HDRS)
SET(SAMPLE_RCS)

######################################################################################


######################################################################################
### 6) Now where we go ?
######################################################################################

ADD_SUBDIRECTORY(resources)
ADD_SUBDIRECTORY(translations)
ADD_SUBDIRECTORY(forms)
ADD_SUBDIRECTORY(includes)
ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(config)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(doc)

######################################################################################


######################################################################################
### 7) Some routines for Qt resources
######################################################################################

# Here is an explaination to how to use qt4_wrap_cpp:
# http://www.mail-archive.com/cmake@cmake.org/msg18900.html

QT4_WRAP_UI(SAMPLE_UIS_SRCS ${SAMPLE_UIS})
QT4_WRAP_CPP(SAMPLE_MOC_SRCS ${SAMPLE_MOC_HDRS})
QT4_ADD_RESOURCES(SAMPLE_RC_SRCS ${SAMPLE_RCS})

# Further details about translation below:
# http://www.cmake.org/Wiki/CMake:How_To_Build_Qt4_Software

######################################################################################


######################################################################################
### 8) Create executable, link libraries and prepare target
######################################################################################

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
LINK_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/lib)

SET(RC_FILE "ceg.rc")

# Comment the following line to enable the console output on windows
IF(WIN32)
	SET(GUI_TYPE WIN32)
	LINK_LIBRARIES(${QT_QTMAIN_LIBRARY})
ENDIF(WIN32)

ADD_EXECUTABLE(
  ${PROJECT_NAME}
  ${GUI_TYPE}
  ${SAMPLE_SRCS}
  ${SAMPLE_UIS_SRCS}
  ${SAMPLE_MOC_SRCS}
  ${SAMPLE_RC_SRCS}
  ${RC_FILE}
  )

SET(CEG_LIBS action)

IF (UNIX)
  TARGET_LINK_LIBRARIES(
    ${PROJECT_NAME}
    ${QT_LIBRARIES}
    ${XMU_LIBRARIES}
    ${X11_LIBRARIES}
    ${XTST_LIBRARIES}
    ${CEG_LIBS}
    )
ELSE()
  TARGET_LINK_LIBRARIES(
    ${PROJECT_NAME}
    ${QT_LIBRARIES}
    ${CEG_LIBS}
    )
ENDIF()

INSTALL(
  TARGETS ${PROJECT_NAME}
  RUNTIME
  DESTINATION bin
  COMPONENT applications
  )

IF(WIN32)
  SET(DLL_SOURCES
    ${QT_BINARY_DIR}/QtGui4.dll
    ${QT_BINARY_DIR}/QtCore4.dll
    ${QT_BINARY_DIR}/QtXml4.dll
    ${QT_BINARY_DIR}/QtNetwork4.dll
    )

  INSTALL(
    FILES ${DLL_SOURCES}
    DESTINATION bin
    COMPONENT libraries
    )
ENDIF()

EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/share ${CMAKE_CURRENT_BINARY_DIR}/share)

INSTALL(DIRECTORY share DESTINATION . COMPONENT applications PATTERN ".svn" EXCLUDE)

######################################################################################


######################################################################################
### 9) Include packaging
######################################################################################

INCLUDE(Packaging.cmake)

######################################################################################
