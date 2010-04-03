TEMPLATE = app

QT += network

LANGUAGE = C++

TARGET = 

DEPENDPATH += . \
    includes \
    src
INCLUDEPATH += . \
    includes


HEADERS += includes/AbstractItem.h \
    includes/AbstractScene.h \
    includes/BoxManager.h \
    includes/DefaultItem.h \
    includes/Layer.h \
    includes/Layout.h \
    includes/MyAweSomeBox.h \
    includes/Window.h \
    includes/WindowGeometry.h \
    includes/AbstractBox.h
SOURCES += src/AbstractItem.cpp \
    src/AbstractScene.cpp \
    src/BoxManager.cpp \
    src/DefaultItem.cpp \
    src/Layer.cpp \
    src/Layout.cpp \
    src/main.cpp \
    src/MyAweSomeBox.cpp \
    src/Window.cpp \
    src/WindowGeometry.cpp \
    src/AbstractBox.cpp

CONFIG += warn_on

DESTDIR = build

OBJECTS_DIR = build

MOC_DIR = moc

UI_SOURCES_DIR = ui_src

UI_HEADERS_DIR = ui_includes
