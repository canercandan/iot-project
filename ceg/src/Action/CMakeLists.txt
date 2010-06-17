INCLUDE_DIRECTORIES(${IOT_CEG_SRC_DIR}/includes/Action)

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

# INSTALL(
#   TARGETS action
#   ARCHIVE
#   DESTINATION lib
#   COMPONENT libraries
#   )
