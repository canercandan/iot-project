######################################################################################
### 1) Set the application properties
######################################################################################

# Checks cmake version compatibility
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(iot)

SET(PROJECT_VERSION_MAJOR 1)
SET(PROJECT_VERSION_MINOR 0)
SET(PROJECT_VERSION_PATCH 0)
SET(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

MESSAGE("IOT SOURCE DIR: " ${CMAKE_SOURCE_DIR})
MESSAGE("IOT PROJECT NAME: " ${PROJECT_NAME})

######################################################################################


######################################################################################
### 2) Now where we go ?
######################################################################################

ADD_SUBDIRECTORY(ceg)
ADD_SUBDIRECTORY(builder)

######################################################################################


######################################################################################
### 3) Include packaging
######################################################################################

INCLUDE(Packaging.cmake)

######################################################################################
