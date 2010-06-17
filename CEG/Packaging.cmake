######################################################################################
### 1) Check dependencies
######################################################################################

IF (NOT DEFINED PROJECT_NAME OR
    NOT DEFINED PROJECT_VERSION_MAJOR OR
    NOT DEFINED PROJECT_VERSION_MINOR OR
    NOT DEFINED PROJECT_VERSION_PATCH OR
    NOT DEFINED PROJECT_VERSION)
  MESSAGE(FATAL_ERROR "Be sure you have defined PROJECT_NAME and PROJECT_VERSION*.")
ENDIF()

######################################################################################


######################################################################################
### 2) Set up components
######################################################################################

SET(CPACK_COMPONENTS_ALL applications libraries)

SET(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "CEG Application")
SET(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION "Here is the main program")

# SET(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
# SET(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "The library can be useful for developpers")

# SET(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Headers")
# SET(CPACK_COMPONENT_HEADERS_DESCRIPTION "The header filers can be useful for developpers")

# SET(CPACK_COMPONENT_HEADERS_DEPENDS libraries)

SET(CPACK_COMPONENT_APPLICATIONS_GROUP "Runtime")
# SET(CPACK_COMPONENT_LIBRARIES_GROUP "Development")
# SET(CPACK_COMPONENT_HEADERS_GROUP "Development")

# SET(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION "All of the tools you'll ever need to develop software")

# SET(CPACK_ALL_INSTALL_TYPES Full Developer)
SET(CPACK_ALL_INSTALL_TYPES Full)

# SET(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full)
# SET(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full)
SET(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)

######################################################################################


######################################################################################
### 3) Set up general information about packaging
######################################################################################

# For more details: http://www.cmake.org/Wiki/CMake:Component_Install_With_CPack

#cpack package information
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(CPACK_PACKAGE_DESCRIPTION "CEG has been developped as part of IOT project and allows users to control machine by thinking.")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "IOT - Graphical Environment Control")
SET(CPACK_PACKAGE_VENDOR "IOnlyThink.com")
SET(CPACK_PACKAGE_CONTACT "ceg@ionlythink.com")
SET(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
SET(CPACK_STRIP_FILES ${PROJECT_NAME})
SET(CPACK_SOURCE_STRIP_FILES "bin/${PROJECT_NAME}")
SET(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "${PROJECT_NAME}")
SET(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "test ${PROJECT_NAME} ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

######################################################################################


######################################################################################
### 3) Set up debian packaging information
######################################################################################

SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libqtgui4, libpng12-0, libsm6, libice6, libxrender1, libfreetype6, libfontconfig1, libxext6, libx11-6, libqt4-xml, libqt4-network, libqt4-core, libglib2.0-cil, libxmu6, libstdc++6, libgcc1, libc6")

SET(CPACK_DEBIAN_PACKAGE_SECTION "tools")
SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

######################################################################################


######################################################################################
### 3) And finally, include cpack, this is the last thing to do.
######################################################################################

INCLUDE(CPack)

######################################################################################
