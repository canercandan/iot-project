TEMPLATE = app
LANGUAGE = C++
TARGET = 
DEPENDPATH += . \
    includes \
    src
INCLUDEPATH += . \
    includes

# Input
HEADERS += includes/Layout.h \
    includes/MyAweSomeBox.h \
    includes/AbstractScene.h \
    includes/Layer.h \
    includes/BoxManager.h
SOURCES += src/Layout.cpp \
    src/main.cpp \
    src/MyAweSomeBox.cpp \
    src/AbstractScene.cpp \
    src/Layer.cpp \
    src/BoxManager.cpp
CONFIG += warn_on
