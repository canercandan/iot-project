# this file create binary of CEG in including all sources files

IF(UNIX)
  INCLUDE(FindPkgConfig)
  PKG_CHECK_MODULES(XMU xmu REQUIRED)
  INCLUDE_DIRECTORIES(${XMU_INCLUDE_DIR})
  LINK_DIRECTORIES(${XMU_LIBRARY_DIRS})
ENDIF()

SET(SAMPLE_SRCS
  AbstractItem.cpp
  AbstractScene.cpp
  ActionFactory.cpp
  BoxController.cpp
  Box.cpp
  BoxStyle.cpp
  CegTcpServer.cpp
  ClickAction.cpp
  CustomItem.cpp
  DefaultItem.cpp
  EventMenuAction.cpp
  GraphicItemFactory.cpp
  Layer.cpp
  MainController.cpp
  main.cpp
  Menu.cpp
  MenuItem.cpp
  MoveAction.cpp
  ReadAction.cpp
  Systray.cpp
  Utils.cpp
  View.cpp
  Window.cpp
  WriteAction.cpp
  ZoomAction.cpp
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

SET(SAMPLE_MOC_HDRS
  ${CMAKE_SOURCE_DIR}/includes/Systray.h
  ${CMAKE_SOURCE_DIR}/includes/CegTcpServer.h
  )

SET(SAMPLE_RCS
  ${CMAKE_SOURCE_DIR}/resources/images.qrc
  )

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

QT4_WRAP_CPP(SAMPLE_MOC_SRCS ${SAMPLE_MOC_HDRS})
QT4_ADD_RESOURCES(SAMPLE_RC_SRCS ${SAMPLE_RCS})

ADD_EXECUTABLE(ceg ${SAMPLE_SRCS} ${SAMPLE_MOC_SRCS} ${SAMPLE_RC_SRCS})

IF(UNIX)
  TARGET_LINK_LIBRARIES(ceg ${QT_LIBRARIES} ${XMU_LIBRARIES} ${X11_LIBRARIES})
ELSEIF(WIN32)
  SET(PSAPI "C:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib\Psapi.Lib")
  TARGET_LINK_LIBRARIES(ceg ${QT_LIBRARIES} ${PSAPI})
ENDIF()
