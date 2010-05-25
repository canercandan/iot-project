# this file create binary of CEG in including all sources files

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

qt4_automoc(${SOURCES})

IF(UNIX)
  SET(SOURCES ${SOURCES} XWindowSystem.cpp)
ELSE (WIN32)
  SET(SOURCES ${SOURCES} Win32Explorer.cpp)
  SET(SOURCES ${SOURCES} Win32Adaptor.cpp)
ENDIF()

QT4_AUTOMOC(${SOURCES})

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(ceg ${SOURCES})

IF(UNIX)
  INCLUDE(FindPkgConfig)
  PKG_CHECK_MODULES(XMU xmu)
  TARGET_LINK_LIBRARIES(ceg ${QT_LIBRARIES} ${XMU_LIBRARIES} ${X11_LIBRARIES})
ELSE()
  TARGET_LINK_LIBRARIES(ceg ${QT_LIBRARIES} "C:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib\Psapi.Lib")
ENDIF()
