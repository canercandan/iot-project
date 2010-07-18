######################################################################################
### Qt translation cmake configuration for CEG
######################################################################################

# thanks to the project http://code.google.com/p/urtconnector

PROJECT(translations)

FILE(GLOB TRANSLATION_FILES *.ts)

FIND_PACKAGE(Qt4 REQUIRED)

QT4_ADD_TRANSLATION(QM_FILES ${TRANSLATION_FILES})

ADD_CUSTOM_TARGET(${PROJECT_NAME} ALL DEPENDS ${QM_FILES})

INSTALL(
  FILES ${QM_FILES}
  DESTINATION share/ceg/translations
  COMPONENT translations
  )

######################################################################################
