######################################################################################
### 1) Create dynamic library for Action classes
######################################################################################

SET(ACTION_SRCS
  ActionFactory.cpp
  ClickAction.cpp
  ExecMenuAction.cpp
  MoveAction.cpp
  PopMenuAction.cpp
  ReadAction.cpp
  ValidAction.cpp
  WriteAction.cpp
  ZoomAction.cpp
  )

SET(LIBRARY_OUTPUT_PATH ${ceg_BINARY_DIR}/lib)

FILE(GLOB ACTION_SRCS *.cpp)
ADD_LIBRARY(action ${ACTION_SRCS})

######################################################################################
