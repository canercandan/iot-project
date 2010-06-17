######################################################################################
### 1) Set the application properties
######################################################################################

# Checks cmake version compatibility
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(builder)

SET(PROJECT_VERSION_MAJOR 1)
SET(PROJECT_VERSION_MINOR 0)
SET(PROJECT_VERSION_PATCH 0)
SET(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

######################################################################################


######################################################################################
### 2) Prepare some useful variables
######################################################################################

SET(IOT_BUILDER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
SET(IOT_BUILDER_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}")

######################################################################################


######################################################################################
### 2) Set target and create executable
######################################################################################

INSTALL(
  TARGETS ${PROJECT_NAME}
  RUNTIME # RUNTIME keyword allows to make binary executable (chmod +x)
  DESTINATION bin
  COMPONENT applications
  )

######################################################################################


######################################################################################
### 3) Include packaging
######################################################################################

INCLUDE(Packaging.cmake)

######################################################################################
