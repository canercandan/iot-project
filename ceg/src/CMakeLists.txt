# this file create binary of CEG in including all sources files

IF(UNIX)
  INCLUDE(FindPkgConfig)
  PKG_CHECK_MODULES(XMU xmu REQUIRED)
ENDIF()

SET(SOURCES
  AbstractBox.cpp
  AbstractItem.cpp
  AbstractScene.cpp
  ActionFactory.cpp
  BoxManager.cpp
  BoxParameter.cpp
  ClickAction.cpp
  DefaultItem.cpp
  EventMenuAction.cpp
  GraphicItemFactory.cpp
  Layer.cpp
  LayerManager.cpp
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
  SET(SOURCES ${SOURCES} XWindowSystem.cpp)
ELSE (WIN32)
  SET(SOURCES ${SOURCES} Win32Explorer.cpp)
  SET(SOURCES ${SOURCES} Win32Adaptor.cpp)
ENDIF()

#QT4_AUTOMOC(${SOURCES})

# Use of qt4_wrap_cpp and qt4_automoc:
# http://qtnode.net/wiki/Qt4_with_cmake

# Here is an explaination to how to use qt4_wrap_cpp:
# http://www.mail-archive.com/cmake@cmake.org/msg18900.html

SET(MOC_HEADERS
  Systray.h
  )

QT4_WRAP_CPP(MOC_SOURCES ${MOC_HEADERS})

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(ceg ${SOURCES} ${MOC_SOURCES})

IF(UNIX)
  TARGET_LINK_LIBRARIES(ceg ${QT_LIBRARIES} ${XMU_LIBRARIES} #${X11_LIBRARIES}
    )
ELSE()
  TARGET_LINK_LIBRARIES(ceg ${QT_LIBRARIES} "C:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib\Psapi.Lib")
ENDIF()
