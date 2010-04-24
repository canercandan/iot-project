SET(QT_USE_QTNETWORK TRUE)

# see http://cmake.org/cmake/help/cmake2.6docs.html#module:FindQt4 for a complete list

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/includes)

IF(UNIX)
  INCLUDE(FindX11)
  INCLUDE_DIRECTORIES(${X11_INCLUDE_DIR})
  LINK_DIRECTORIES(${X11_LIBRARY_DIRS})

  IF (CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -g3")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
  ENDIF()
ENDIF()

SET(SOURCES
  AbstractItem.cpp
  AbstractScene.cpp
  BoxManager.cpp
  DefaultItem.cpp
  Layer.cpp
  main.cpp
  Window.cpp
  WindowGeometry.cpp
  AbstractBox.cpp
  GraphicItemFactory.cpp
  LayerManager.cpp
  ZoomAction.cpp
  ClickAction.cpp
  ReadAction.cpp
  MoveAction.cpp
  WriteAction.cpp
  View.cpp
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
