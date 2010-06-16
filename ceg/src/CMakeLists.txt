# this file create binary of CEG in including all sources files

IF(UNIX)
  INCLUDE(FindPkgConfig)
  PKG_CHECK_MODULES(XMU xmu REQUIRED)
  INCLUDE_DIRECTORIES(${XMU_INCLUDE_DIR})
  LINK_DIRECTORIES(${XMU_LIBRARY_DIRS})
ENDIF()

ADD_SUBDIRECTORY(Action)

SET(SAMPLE_SRCS
  AbstractItem.cpp
  AbstractScene.cpp
  BoxController.cpp
  Box.cpp
  BoxStyle.cpp
  CegTcpServer.cpp
  CustomItem.cpp
  DefaultItem.cpp
  GraphicItemFactory.cpp
  Layer.cpp
  MainController.cpp
  main.cpp
  Menu.cpp
  MenuItem.cpp
  Settings.cpp
  Systray.cpp
  Utils.cpp
  View.cpp
  Window.cpp
)

IF(UNIX)
  SET(SAMPLE_SRCS ${SAMPLE_SRCS} XWindowSystem.cpp)
ELSEIF(WIN32)
  SET(SAMPLE_SRCS ${SAMPLE_SRCS} Win32Explorer.cpp)
  SET(SAMPLE_SRCS ${SAMPLE_SRCS} Win32Adaptor.cpp)
ENDIF()

#QT4_AUTOMOC(${SOURCES})

# Use of qt4_wrap_cpp and qt4_automoc:
# http://qtnode.net/wiki/Qt4_with_cmake

# Here is an explaination to how to use qt4_wrap_cpp:
# http://www.mail-archive.com/cmake@cmake.org/msg18900.html

SET(SAMPLE_UIS
  ${IOT_CEG_SRC_DIR}/forms/settings.ui
)

SET(SAMPLE_MOC_HDRS
  ${IOT_CEG_SRC_DIR}/includes/Systray.h
  ${IOT_CEG_SRC_DIR}/includes/Settings.h
  ${IOT_CEG_SRC_DIR}/includes/CegTcpServer.h
  )

SET(SAMPLE_RCS
  ${IOT_CEG_SRC_DIR}/resources/application.qrc
  )

SET(EXECUTABLE_OUTPUT_PATH ${IOT_CEG_BIN_DIR})

QT4_WRAP_UI(SAMPLE_UIS_SRCS ${SAMPLE_UIS})
QT4_WRAP_CPP(SAMPLE_MOC_SRCS ${SAMPLE_MOC_HDRS})
QT4_ADD_RESOURCES(SAMPLE_RC_SRCS ${SAMPLE_RCS})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(${PROJECT_NAME} ${SAMPLE_SRCS} ${SAMPLE_UIS_SRCS} ${SAMPLE_MOC_SRCS} ${SAMPLE_RC_SRCS} )

SET(CEG_LIBS action)

IF(UNIX)
  TARGET_LINK_LIBRARIES(ceg ${QT_LIBRARIES} ${XMU_LIBRARIES} ${X11_LIBRARIES} ${CEG_LIBS})
ELSEIF(WIN32)
  SET(PSAPI "C:/Program Files/Microsoft SDKs/Windows/v7.0A/Lib/Psapi.Lib")
  TARGET_LINK_LIBRARIES(ceg ${QT_LIBRARIES} ${PSAPI} ${CEG_LIBS})
ENDIF()

INSTALL(
  TARGETS ${PROJECT_NAME}
  RUNTIME # RUNTIME keyword allows to make binary executable (chmod +x)
  DESTINATION bin
  COMPONENT applications
  )
