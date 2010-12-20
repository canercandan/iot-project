# this file allows to add test files and their resources

SET(TEST_LIST
  qtxml
  sax
  validator
)

SET(RESOURCE_LIST
  schema.xsd
  firefox.xml
  )

FOREACH(current ${TEST_LIST})
  ADD_EXECUTABLE(${current} ${current}.cpp)
  TARGET_LINK_LIBRARIES(${current} ${QT_LIBRARIES})
ENDFOREACH()

FOREACH(current ${RESOURCE_LIST})
  EXECUTE_PROCESS(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/${current}
    ${CMAKE_CURRENT_BINARY_DIR}/${current}
    )
  MESSAGE(STATUS "${current} file copied")
ENDFOREACH()
