# this file create binary of CEG in including all sources files

SET(SOURCES
  AbstractItem.cpp
  AbstractScene.cpp
  BoxManager.cpp
  DefaultItem.cpp
  Layer.cpp
  main.cpp
  Window.cpp
  AbstractBox.cpp
  GraphicItemFactory.cpp
  LayerManager.cpp
  ZoomAction.cpp
  ClickAction.cpp
  ReadAction.cpp
  MoveAction.cpp
  WriteAction.cpp
  View.cpp
  ActionFactory.cpp
  Menu.cpp
  MenuItem.cpp
  EventMenuAction.cpp
)

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
