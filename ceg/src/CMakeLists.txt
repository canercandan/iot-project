# this file create binary of CEG in including all sources files

ADD_SUBDIRECTORY(Action)

#FILE(GLOB_RECURSE SAMPLE_SRCS *.cpp)

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
  )

IF (UNIX)
  SET(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/XWindowSystem.cpp)
ELSEIF(WIN32)
  SET(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Win32Explorer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Win32Adaptor.cpp
    )
ENDIF()

SET(SAMPLE_SRCS ${SOURCES} PARENT_SCOPE)

#QT4_AUTOMOC(${SOURCES})

# Use of qt4_wrap_cpp and qt4_automoc:
# http://qtnode.net/wiki/Qt4_with_cmake

# Here is an explaination to how to use qt4_wrap_cpp:
# http://www.mail-archive.com/cmake@cmake.org/msg18900.html

# SET(SAMPLE_UIS
#   ${IOT_CEG_SRC_DIR}/forms/settings.ui
# )

# SET(SAMPLE_MOC_HDRS
#   ${IOT_CEG_SRC_DIR}/includes/Systray.h
#   ${IOT_CEG_SRC_DIR}/includes/Settings.h
#   ${IOT_CEG_SRC_DIR}/includes/CegTcpServer.h
#   )

# SET(SAMPLE_RCS
#   ${IOT_CEG_SRC_DIR}/resources/application.qrc
#   )

# SET(EXECUTABLE_OUTPUT_PATH ${IOT_CEG_BIN_DIR})


# http://www.cmake.org/Wiki/CMake:How_To_Build_Qt4_Software
#QT4_ADD_TRANSLATION(SAMPLE_TRANS_SRCS ${TRANSLATIONS})

#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# ADD_EXECUTABLE(${PROJECT_NAME} ${SAMPLE_SRCS} ${SAMPLE_UIS_SRCS} ${SAMPLE_MOC_SRCS} ${SAMPLE_RC_SRCS} ${SAMPLE_TRANS_SRCS})

# SET(CEG_LIBS action)

# IF(UNIX)
#   TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES} ${XMU_LIBRARIES} ${X11_LIBRARIES} ${CEG_LIBS})
# ELSEIF(WIN32)
#   SET(PSAPI "C:/Program Files/Microsoft SDKs/Windows/v7.0A/Lib/Psapi.Lib")
#   TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES} ${PSAPI} ${CEG_LIBS})
# ENDIF()

# INSTALL(
#   TARGETS ${PROJECT_NAME}
#   RUNTIME # RUNTIME keyword allows to make binary executable (chmod +x)
#   DESTINATION bin
#   COMPONENT applications
#   )
