INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/includes/Action)

SET(ACTION_SRCS
  ActionFactory.cpp
  ClickAction.cpp
  ExecMenuAction.cpp
  MoveAction.cpp
  PopMenuAction.cpp
  ReadAction.cpp
  WriteAction.cpp
  ZoomAction.cpp
  )

ADD_LIBRARY(action ${ACTION_SRCS})
