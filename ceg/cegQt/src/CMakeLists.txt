IF(UNIX)
  INCLUDE(FindX11)
ENDIF()

SET(QT_USE_QTNETWORK TRUE)

# see http://cmake.org/cmake/help/cmake2.6docs.html#module:FindQt4 for a complete list

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/includes)
INCLUDE_DIRECTORIES(${X11_INCLUDE_DIR})

LINK_DIRECTORIES(${X11_LIBRARY_DIRS})

FILE(
  GLOB_RECURSE
  SOURCES
  *.cpp
  )

IF(UNIX)
  LIST (REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Win32Explorer.cpp")
  LIST (REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Win32Adaptor.cpp")
ELSE (WIN32)
  LIST (REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/XWindowSystem.cpp")
ENDIF()

# SET(MOC_SOURCES
#   includes/AbstractItem.h
#   includes/AbstractScene.h
#   includes/BoxManager.h
#   includes/DefaultItem.h
#   includes/Layer.h
#   includes/Window.h
#   includes/WindowGeometry.h
#   includes/AbstractBox.h
#   includes/GraphicItemFactory.h
#   includes/LayerManager.h
#   includes/TypeToString.hpp
#   includes/ICommunicationGraphicalServer.h
#   )

#QT4_WRAP_CPP(SOURCES ${MOC_SOURCES})

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
