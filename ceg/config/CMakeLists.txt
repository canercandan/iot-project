# FIXME: Pose probleme car recupére un chemin absolut
# donc inutilisable dans EXECUTE_PROCESS
# ------
# FILE(
#   GLOB_RECURSE
#   SOURCES
#   *.xml
#   )
# ------

# donc pour le moment on liste chaque fichier de config ci-dessous
SET(SOURCES
  sample.xml
  firefox.xml
  )

FOREACH(current ${SOURCES})
  EXECUTE_PROCESS(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/box/${current}
    ${CMAKE_CURRENT_BINARY_DIR}/box/${current}
    )
  MESSAGE(STATUS "${current} file copied")
ENDFOREACH()
