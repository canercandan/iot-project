######################################################################################
### 1) Create dynamic library for Action classes
######################################################################################

PROJECT(action)

SET(LIBRARY_OUTPUT_PATH ${ceg_BINARY_DIR}/lib)

FILE(GLOB ACTION_SRCS *.cpp)

ADD_LIBRARY(${PROJECT_NAME} ${ACTION_SRCS})

######################################################################################
