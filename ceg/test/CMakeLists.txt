###############################################################################
##
## CMakeLists file for iot-ceg/test
##
###############################################################################

INCLUDE(FindPkgConfig)
INCLUDE(FindX11)

pkg_check_modules(GTK2 gtk+-2.0)
pkg_check_modules(XMU xmu)

######################################################################################
### 1) Include the sources
######################################################################################

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${GTK2_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${GTKMM_INCLUDE_DIRS})

######################################################################################


######################################################################################
### 2) Specify where CMake can find the libraries
######################################################################################

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)
LINK_DIRECTORIES(${GTK2_LIBRARY_DIRS})
LINK_DIRECTORIES(${GTKMM_LIBRARY_DIRS})

######################################################################################


######################################################################################
### 3) Define your targets and link the librairies
######################################################################################

SET (TEST_LIST
  t-xlsclients
  t-print_window_names_on_X11
  t-gtk2
  t-transparency
  t-transparency2
  t-transparency_easy_way
  t-table
  t-window_in_window
#  t-vnc_simple
#  t-vnc_ev
  t-smallmatrix
  t-socket
  t-plug
  t-timerexample
  t-monitoring
  t-keypressed
  t-XEvent
  t-X11
  t-logger
)

FOREACH (test ${TEST_LIST})
  SET ("T_${test}_SOURCES" "${test}.cpp")
ENDFOREACH (test)

#CREATE EXECUTABLES AND ADD ITS AS TEST
FOREACH (test ${TEST_LIST})
  ADD_EXECUTABLE(${test} ${T_${test}_SOURCES})
  #ADD_DEPENDENCIES(${test} SOMETHING)
  ADD_TEST(${test} ${test})
ENDFOREACH (test)

ADD_DEPENDENCIES(t-gtk2 ${GTK2_CFLAGS})

# Link the librairies
FOREACH (test ${TEST_LIST})
  TARGET_LINK_LIBRARIES(${test} ${GTKMM_LIBRARIES})
ENDFOREACH (test)

TARGET_LINK_LIBRARIES(t-xlsclients ${X11_LIBRARIES} ${XMU_LIBRARIES})
TARGET_LINK_LIBRARIES(t-print_window_names_on_X11 ${X11_LIBRARIES} ${XMU_LIBRARIES})
TARGET_LINK_LIBRARIES(t-gtk2 ${GTK2_LIBRARIES})
#TARGET_LINK_LIBRARIES(t-vnc_simple -lvncserver)
#TARGET_LINK_LIBRARIES(t-vnc_ev -lvncserver)
TARGET_LINK_LIBRARIES(t-XEvent ${X11_LIBRARIES} ${XMU_LIBRARIES})
TARGET_LINK_LIBRARIES(t-X11 ${X11_LIBRARIES} ${XMU_LIBRARIES})

######################################################################################
