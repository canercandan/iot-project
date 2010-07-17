######################################################################################
### 1) Set all needed source files for the project
######################################################################################

SET(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/AbstractItem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AbstractScene.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/BoxController.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Box.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/BoxStyle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CegTcpServer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CustomItem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/DefaultItem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GraphicItemFactory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Layer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MainController.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Menu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MenuItem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Settings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Systray.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/View.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/QuitHandler.cpp
  )

IF (UNIX)
  SET(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/XWindowSystem.cpp)
ELSEIF(WIN32)
  IF (NOT MINGW)
    SET(SOURCES ${SOURCES}
      ${CMAKE_CURRENT_SOURCE_DIR}/Win32Explorer.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/Win32Adaptor.cpp
      )
  ELSE()
    #SET(SOURCES ${SOURCES})
  ENDIF()
ENDIF()

SET(SAMPLE_SRCS ${SOURCES} PARENT_SCOPE)

######################################################################################


######################################################################################
### 2) Now where we go ?!?
######################################################################################

ADD_SUBDIRECTORY(Action)

######################################################################################
