#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENABLE_PEO")

######################################################################################
### 1) Include the sources
######################################################################################

#INCLUDE_DIRECTORIES()

######################################################################################


######################################################################################
### 2) Specify where CMake can find the libraries
######################################################################################

#LINK_DIRECTORIES()
######################################################################################


######################################################################################
### 3) Define your target: just an executable here
######################################################################################

SET(SUFFIX_PATH "application/example")
SET(FILE_TO_COPY
  example.xml
)

FOREACH(file ${FILE_TO_COPY})
  EXECUTE_PROCESS(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_SOURCE_DIR}/${SUFFIX_PATH}/${file}
      ${CMAKE_BINARY_DIR}/${SUFFIX_PATH}
  )
ENDFOREACH(file)

#ADD_LIBRARY()
#ADD_EXECUTABLE(example main.cpp)
#ADD_DEPENDENCIES(example LIB)

######################################################################################


######################################################################################
### 4) Link the librairies for your executable
######################################################################################

# Only if you need to link libraries
#TARGET_LINK_LIBRARIES(example LIB)

######################################################################################


######################################################################################
### 5) Copy the instances and the "param" file in the build path for an easy use.
###
### --> run the "make install" target to copy the parameter file / instances
###	in the directory where you build the application
######################################################################################

ADD_CUSTOM_TARGET(install DEPENDS ${CMAKE_SOURCE_DIR}/application/example.param
  ${CMAKE_SOURCE_DIR}/application)
ADD_CUSTOM_COMMAND(
  TARGET install
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy_if_different
  ${CMAKE_SOURCE_DIR}/application/example.param
  ${CMAKE_BINARY_DIR}/application
  )

######################################################################################
