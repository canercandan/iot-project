######################################################################################
### 0) Find need packages
######################################################################################

#FIND_PACKAGE(Boost 1.33.0 COMPONENTS program_options)

######################################################################################

#IF(Boost_FOUND)

######################################################################################
### 1) Include the sources
######################################################################################

INCLUDE_DIRECTORIES(${GTKMM_INCLUDE_DIRS} #${Boost_INCLUDE_DIRS}
)

######################################################################################


######################################################################################
### 2) Specify where CMake can find the libraries
######################################################################################

LINK_DIRECTORIES(${GTKMM_LIBRARY_DIRS} #${Boost_LIBRARY_DIRS}
)

######################################################################################


######################################################################################
### 3) Define your target(s): just an executable here
######################################################################################
SET(SOURCES
  main.cpp
  WindowManager.cpp
  Grid.cpp
  Area.cpp
  Layer.cpp
  DefaultGrid.cpp
  CommonWindow.cpp
  MenuWindow.cpp
  MenuGrid.cpp
  EventMenuGrid.cpp
  NavigationMenuGrid.cpp
  MenuArea.cpp
  )

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(ceg ${SOURCES})
#ADD_DEPENDENCIES(ceg)

######################################################################################


######################################################################################
### 3) Link the librairies for your executable
######################################################################################

# Only if you need to link libraries
TARGET_LINK_LIBRARIES(ceg ${GTKMM_LIBRARIES} #${Boost_LIBRARIES}
)

######################################################################################

# ELSE()

# MESSAGE(ERROR "Boost not available in your system")

# ENDIF()
