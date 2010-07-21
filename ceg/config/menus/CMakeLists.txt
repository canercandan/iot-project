FILE(GLOB SOURCES *.xml)

FOREACH(current ${SOURCES})
  EXECUTE_PROCESS(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${current}
    ${CMAKE_CURRENT_BINARY_DIR}/
    )
  MESSAGE(STATUS "${current} file copied")
ENDFOREACH()

FILE(GLOB SOURCES ${CMAKE_CURRENT_BINARY_DIR}/*.xml)

INSTALL(
  FILES ${SOURCES}
  DESTINATION share/ceg/config/menus
  COMPONENT applications
  )

# ADD_SUBDIRECTORY(en_US)
# ADD_SUBDIRECTORY(fr_FR)
