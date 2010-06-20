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

SET(LIBRARY_OUTPUT_PATH ${IOT_CEG_BIN_DIR}/lib)

ADD_LIBRARY(action ${ACTION_SRCS})

# INSTALL(
#   TARGETS action
#   ARCHIVE
#   DESTINATION lib
#   COMPONENT libraries
#   )
