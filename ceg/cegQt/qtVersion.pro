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
    includes/Window.h \
    includes/WindowGeometry.h \
    includes/AbstractBox.h \
    includes/GraphicItemFactory.h \
    includes/LayerManager.h \
    includes/TypeToString.hpp \
    includes/ICommunicationGraphicalServer.h

SOURCES += src/AbstractItem.cpp \
    src/AbstractScene.cpp \
    src/BoxManager.cpp \
    src/DefaultItem.cpp \
    src/Layer.cpp \
    src/main.cpp \
    src/Window.cpp \
    src/WindowGeometry.cpp \
    src/AbstractBox.cpp \
    src/GraphicItemFactory.cpp \
    src/LayerManager.cpp


#win32
#{
#    HEADERS += includes/Win32Adaptor.h \
#                includes/Win32Explorer.h
#    SOURCES +=  src/Win32Adaptor.h \
#                src/Win32Explorer.h
#}

CONFIG += warn_on

DESTDIR = build

OBJECTS_DIR = build

MOC_DIR = moc

UI_SOURCES_DIR = ui_src

UI_HEADERS_DIR = ui_includes
