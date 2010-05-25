SET(SOURCES
  sample.xml
  )

FOREACH(current ${SOURCES})
  EXECUTE_PROCESS(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/${current}
    ${CMAKE_CURRENT_BINARY_DIR}/${current}
    )
  MESSAGE(STATUS "${current} file copied")
ENDFOREACH()
